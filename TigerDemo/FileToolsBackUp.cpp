#include "FileToolsBackUp.h"
#include "OsUtils.h"
#include "endianness.h"
#include <dirent.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/installation_proxy.h>
#include <libimobiledevice/sbservices.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <libimobiledevice-glue/utils.h>
#ifdef __cplusplus
}
#endif

// 宏
#define PACKAGE_URL "YiXuan"
#define PACKAGE_BUGREPORT "YiXuan_SH"
#define PACKAGE_VERSION "1.0"

#define TOOL_NAME "idevicebackup2"

#define LOCK_ATTEMPTS 50
#define LOCK_WAIT 200000

#define CODE_SUCCESS 0x00
#define CODE_ERROR_LOCAL 0x06
#define CODE_ERROR_REMOTE 0x0b
#define CODE_FILE_DATA 0x0c

#define OPT_SYSTEM 1
#define OPT_REBOOT 2
#define OPT_NO_REBOOT 3
#define OPT_COPY 4
#define OPT_SETTINGS 5
#define OPT_REMOVE 6
#define OPT_SKIP_APPS 7
#define OPT_PASSWORD 8
#define OPT_FULL 9

#define DEVICE_VERSION(maj, min, patch) ((((maj) & 0xFF) << 16) | (((min) & 0xFF) << 8) | ((patch) & 0xFF))
#define PRINT_VERBOSE(min_level, ...) if (1 >= min_level) { printf(__VA_ARGS__); };


FileToolsBackUp::FileToolsBackUp(QObject *parent)
    :QObject(parent)
{

}

FileToolsBackUp::~FileToolsBackUp()
{

}

int FileToolsBackUp::quit_flag = 0;
int FileToolsBackUp::backup_domain_changed = 0;
double FileToolsBackUp::overall_progress = 0;


/*
 * 设置NP通知的回调函数
 * 作为NP通知的回调函数，当用户取消备份操作或者备份域发生了改变
 * 则手机端会调用该函数，进而改变全局变量，控制PC端的备份进程
*/
void FileToolsBackUp::notify_cb(const char *notification, void *userdata)
{
    if (strlen(notification) == 0) {
        return;
    }
    if (!strcmp(notification, NP_SYNC_CANCEL_REQUEST)) {
        PRINT_VERBOSE(1, "User has cancelled the backup process on the device.\n");
        quit_flag++;
    } else if (!strcmp(notification, NP_BACKUP_DOMAIN_CHANGED)) {
        backup_domain_changed = 1;
    } else {
        PRINT_VERBOSE(1, "Unhandled notification '%s' (TODO: implement)\n", notification);
    }
}

/*
 * 从AFC客户端对象获取指定文件的内容
*/
void FileToolsBackUp::mobilebackup_afc_get_file_contents(afc_client_t afc, const char *filename, char **data, uint64_t *size)
{
    if (!afc || !data || !size) {
        return;
    }

    char **fileinfo = NULL;
    uint32_t fsize = 0;

    afc_get_file_info(afc, filename, &fileinfo);
    if (!fileinfo) {
        return;
    }
    int i;
    for (i = 0; fileinfo[i]; i+=2) {
        if (!strcmp(fileinfo[i], "st_size")) {
            fsize = atol(fileinfo[i+1]);
            break;
        }
    }
    afc_dictionary_free(fileinfo);

    if (fsize == 0) {
        return;
    }

    uint64_t f = 0;
    afc_file_open(afc, filename, AFC_FOPEN_RDONLY, &f);
    if (!f) {
        return;
    }
    char *buf = (char*)malloc((uint32_t)fsize);
    uint32_t done = 0;
    while (done < fsize) {
        uint32_t bread = 0;
        afc_file_read(afc, f, buf+done, 65536, &bread);
        if (bread > 0) {
            done += bread;
        } else {
            break;
        }
    }
    if (done == fsize) {
        *size = fsize;
        *data = buf;
    } else {
        free(buf);
    }
    afc_file_close(afc, f);
}

/*
 * 生产uuid
 * 作用：？
*/
char* FileToolsBackUp::get_uuid()
{
    const char *chars = "ABCDEF0123456789";
    int i = 0;
    char *uuid = (char*)malloc(sizeof(char) * 33);

    srand(time(NULL));

    for (i = 0; i < 32; i++) {
        uuid[i] = chars[rand() % 16];
    }

    uuid[32] = '\0';

    return uuid;
}

/*
 * 生成info.plist文件
*/
plist_t FileToolsBackUp::mobilebackup_factory_info_plist_new(const char* udid, idevice_t device, afc_client_t afc)
{
    /* gather data from lockdown */
    plist_t value_node = NULL;
    plist_t root_node = NULL;
    plist_t itunes_settings = NULL;
    plist_t min_itunes_version = NULL;
    char *udid_uppercase = NULL;

    lockdownd_client_t lockdown = NULL;
    if (lockdownd_client_new_with_handshake(device, &lockdown, TOOL_NAME) != LOCKDOWN_E_SUCCESS) {
        return NULL;
    }

    plist_t ret = plist_new_dict();

    /* get basic device information in one go */
    lockdownd_get_value(lockdown, NULL, NULL, &root_node);

    /* get iTunes settings */
    lockdownd_get_value(lockdown, "com.apple.iTunes", NULL, &itunes_settings);

    /* get minimum iTunes version */
    lockdownd_get_value(lockdown, "com.apple.mobile.iTunes", "MinITunesVersion", &min_itunes_version);

    lockdownd_client_free(lockdown);

    /* get a list of installed user applications */
    plist_t app_dict = plist_new_dict();
    plist_t installed_apps = plist_new_array();
    instproxy_client_t ip = NULL;
    if (instproxy_client_start_service(device, &ip, TOOL_NAME) == INSTPROXY_E_SUCCESS) {
        plist_t client_opts = instproxy_client_options_new();
        instproxy_client_options_add(client_opts, "ApplicationType", "User", NULL);
        instproxy_client_options_set_return_attributes(client_opts, "CFBundleIdentifier", "ApplicationSINF", "iTunesMetadata", NULL);

        plist_t apps = NULL;
        instproxy_browse(ip, client_opts, &apps);

        sbservices_client_t sbs = NULL;
        if (sbservices_client_start_service(device, &sbs, TOOL_NAME) != SBSERVICES_E_SUCCESS) {
            printf("Couldn't establish sbservices connection. Continuing anyway.\n");
        }

        if (apps && (plist_get_node_type(apps) == PLIST_ARRAY)) {
            uint32_t app_count = plist_array_get_size(apps);
            uint32_t i;
            for (i = 0; i < app_count; i++) {
                plist_t app_entry = plist_array_get_item(apps, i);
                plist_t bundle_id = plist_dict_get_item(app_entry, "CFBundleIdentifier");
                if (bundle_id) {
                    char *bundle_id_str = NULL;
                    plist_array_append_item(installed_apps, plist_copy(bundle_id));

                    plist_get_string_val(bundle_id, &bundle_id_str);
                    plist_t sinf = plist_dict_get_item(app_entry, "ApplicationSINF");
                    plist_t meta = plist_dict_get_item(app_entry, "iTunesMetadata");
                    if (sinf && meta) {
                        plist_t adict = plist_new_dict();
                        plist_dict_set_item(adict, "ApplicationSINF", plist_copy(sinf));
                        if (sbs) {
                            char *pngdata = NULL;
                            uint64_t pngsize = 0;
                            sbservices_get_icon_pngdata(sbs, bundle_id_str, &pngdata, &pngsize);
                            if (pngdata) {
                                plist_dict_set_item(adict, "PlaceholderIcon", plist_new_data(pngdata, pngsize));
                                free(pngdata);
                            }
                        }
                        plist_dict_set_item(adict, "iTunesMetadata", plist_copy(meta));
                        plist_dict_set_item(app_dict, bundle_id_str, adict);
                    }
                    free(bundle_id_str);
                }
            }
        }
        plist_free(apps);

        if (sbs) {
            sbservices_client_free(sbs);
        }

        instproxy_client_options_free(client_opts);

        instproxy_client_free(ip);
    }

    /* Applications */
    plist_dict_set_item(ret, "Applications", app_dict);

    /* set fields we understand */
    value_node = plist_dict_get_item(root_node, "BuildVersion");
    plist_dict_set_item(ret, "Build Version", plist_copy(value_node));

    value_node = plist_dict_get_item(root_node, "DeviceName");
    plist_dict_set_item(ret, "Device Name", plist_copy(value_node));
    plist_dict_set_item(ret, "Display Name", plist_copy(value_node));

    char *uuid = get_uuid();
    plist_dict_set_item(ret, "GUID", plist_new_string(uuid));
    free(uuid);

    value_node = plist_dict_get_item(root_node, "IntegratedCircuitCardIdentity");
    if (value_node)
        plist_dict_set_item(ret, "ICCID", plist_copy(value_node));

    value_node = plist_dict_get_item(root_node, "InternationalMobileEquipmentIdentity");
    if (value_node)
        plist_dict_set_item(ret, "IMEI", plist_copy(value_node));

    /* Installed Applications */
    plist_dict_set_item(ret, "Installed Applications", installed_apps);

    plist_dict_set_item(ret, "Last Backup Date", plist_new_date(time(NULL) - MAC_EPOCH, 0));

    value_node = plist_dict_get_item(root_node, "MobileEquipmentIdentifier");
    if (value_node)
        plist_dict_set_item(ret, "MEID", plist_copy(value_node));

    value_node = plist_dict_get_item(root_node, "PhoneNumber");
    if (value_node && (plist_get_node_type(value_node) == PLIST_STRING)) {
        plist_dict_set_item(ret, "Phone Number", plist_copy(value_node));
    }

    /* FIXME Product Name */

    value_node = plist_dict_get_item(root_node, "ProductType");
    plist_dict_set_item(ret, "Product Type", plist_copy(value_node));

    value_node = plist_dict_get_item(root_node, "ProductVersion");
    plist_dict_set_item(ret, "Product Version", plist_copy(value_node));

    value_node = plist_dict_get_item(root_node, "SerialNumber");
    plist_dict_set_item(ret, "Serial Number", plist_copy(value_node));

    /* FIXME Sync Settings? */

    value_node = plist_dict_get_item(root_node, "UniqueDeviceID");
    plist_dict_set_item(ret, "Target Identifier", plist_new_string(udid));

    plist_dict_set_item(ret, "Target Type", plist_new_string("Device"));

    /* uppercase */
    udid_uppercase = string_toupper((char*)udid);
    plist_dict_set_item(ret, "Unique Identifier", plist_new_string(udid_uppercase));
    free(udid_uppercase);

    char *data_buf = NULL;
    uint64_t data_size = 0;
    mobilebackup_afc_get_file_contents(afc, "/Books/iBooksData2.plist", &data_buf, &data_size);
    if (data_buf) {
        plist_dict_set_item(ret, "iBooks Data 2", plist_new_data(data_buf, data_size));
        free(data_buf);
    }

    plist_t files = plist_new_dict();
    const char *itunesfiles[] = {
        "ApertureAlbumPrefs",
        "IC-Info.sidb",
        "IC-Info.sidv",
        "PhotosFolderAlbums",
        "PhotosFolderName",
        "PhotosFolderPrefs",
        "VoiceMemos.plist",
        "iPhotoAlbumPrefs",
        "iTunesApplicationIDs",
        "iTunesPrefs",
        "iTunesPrefs.plist",
        NULL
    };
    int i = 0;
    for (i = 0; itunesfiles[i]; i++) {
        data_buf = NULL;
        data_size = 0;
        char *fname = (char*)malloc(strlen("/iTunes_Control/iTunes/") + strlen(itunesfiles[i]) + 1);
        strcpy(fname, "/iTunes_Control/iTunes/");
        strcat(fname, itunesfiles[i]);
        mobilebackup_afc_get_file_contents(afc, fname, &data_buf, &data_size);
        free(fname);
        if (data_buf) {
            plist_dict_set_item(files, itunesfiles[i], plist_new_data(data_buf, data_size));
            free(data_buf);
        }
    }
    plist_dict_set_item(ret, "iTunes Files", files);

    plist_dict_set_item(ret, "iTunes Settings", itunes_settings ? plist_copy(itunes_settings) : plist_new_dict());

    /* since we usually don't have iTunes, let's get the minimum required iTunes version from the device */
    if (min_itunes_version) {
        plist_dict_set_item(ret, "iTunes Version", plist_copy(min_itunes_version));
    } else {
        plist_dict_set_item(ret, "iTunes Version", plist_new_string("10.0.1"));
    }

    plist_free(itunes_settings);
    plist_free(min_itunes_version);
    plist_free(root_node);

    return ret;
}

/*
 * 通过mb2状态检查快照状态 ？？？
*/
int FileToolsBackUp::mb2_status_check_snapshot_state(const char *path, const char *udid, const char *matches)
{
    int ret = 0;
    plist_t status_plist = NULL;
    char *file_path = string_build_path(path, udid, "Status.plist", NULL);

    plist_read_from_file(file_path, &status_plist, NULL);
    free(file_path);
    if (!status_plist) {
        printf("Could not read Status.plist!\n");
        return ret;
    }
    plist_t node = plist_dict_get_item(status_plist, "SnapshotState");
    if (node && (plist_get_node_type(node) == PLIST_STRING)) {
        char* sval = NULL;
        plist_get_string_val(node, &sval);
        if (sval) {
            ret = (strcmp(sval, matches) == 0) ? 1 : 0;
            free(sval);
        }
    } else {
        printf("%s: ERROR could not get SnapshotState key from Status.plist!\n", __func__);
    }
    plist_free(status_plist);
    return ret;
}

/*
 * 打开手机端指定的文件
*/
void FileToolsBackUp::do_post_notification(idevice_t device, const char *notification)
{
    lockdownd_service_descriptor_t service = NULL;
    np_client_t np;

    lockdownd_client_t lockdown = NULL;

    if (lockdownd_client_new_with_handshake(device, &lockdown, TOOL_NAME) != LOCKDOWN_E_SUCCESS) {
        return;
    }

    lockdownd_error_t ldret = lockdownd_start_service(lockdown, NP_SERVICE_NAME, &service);
    if (ldret == LOCKDOWN_E_SUCCESS) {
        np_client_new(device, service, &np);
        if (np) {
            np_post_notification(np, notification);
            np_client_free(np);
        }
    } else {
        printf("ERROR: Could not start service %s: %s\n", NP_SERVICE_NAME, lockdownd_strerror(ldret));
    }

    if (service) {
        lockdownd_service_descriptor_free(service);
        service = NULL;
    }
    lockdownd_client_free(lockdown);
}

/*
 * 打印进度条
*/
void FileToolsBackUp::print_progress_real(double progress, int flush)
{
    int i = 0;
    PRINT_VERBOSE(1, "\r[");
    for(i = 0; i < 50; i++) {
        if(i < progress / 2) {
            PRINT_VERBOSE(1, "=");
        } else {
            PRINT_VERBOSE(1, " ");
        }
    }
    PRINT_VERBOSE(1, "] %3.0f%%", progress);

    if (flush > 0) {
        fflush(stdout);
        if (progress == 100)
            PRINT_VERBOSE(1, "\n");
    }
}

/*
 * 计算进度 并 打印进度条
*/
void FileToolsBackUp::print_progress(uint64_t current, uint64_t total)
{
    char *format_size = NULL;
    double progress = ((double)current/(double)total)*100;
    if (progress < 0)
        return;

    if (progress > 100)
        progress = 100;

    print_progress_real((double)progress, 0);

    format_size = string_format_size(current);
    PRINT_VERBOSE(1, " (%s", format_size);
    free(format_size);
    format_size = string_format_size(total);
    PRINT_VERBOSE(1, "/%s)     ", format_size);
    free(format_size);

    fflush(stdout);
    if (progress == 100)
        PRINT_VERBOSE(1, "\n");
}


/*
 * 设置整体进度
*/
void FileToolsBackUp::mb2_set_overall_progress(double progress)
{
    if (progress > 0.0)
        overall_progress = progress;
}

/*
 * 从消息中获取整体进度
*/
void FileToolsBackUp::mb2_set_overall_progress_from_message(plist_t message, char* identifier)
{
    plist_t node = NULL;
    double progress = 0.0;

    if (!strcmp(identifier, "DLMessageDownloadFiles")) {
        node = plist_array_get_item(message, 3);
    } else if (!strcmp(identifier, "DLMessageUploadFiles")) {
        node = plist_array_get_item(message, 2);
    } else if (!strcmp(identifier, "DLMessageMoveFiles") || !strcmp(identifier, "DLMessageMoveItems")) {
        node = plist_array_get_item(message, 3);
    } else if (!strcmp(identifier, "DLMessageRemoveFiles") || !strcmp(identifier, "DLMessageRemoveItems")) {
        node = plist_array_get_item(message, 3);
    }

    if (node != NULL) {
        plist_get_real_val(node, &progress);
        mb2_set_overall_progress(progress);
    }
}

/*
 * 往mb2状态描述变量里添加文件错误
*/
void FileToolsBackUp::mb2_multi_status_add_file_error(plist_t status_dict, const char *path, int error_code, const char *error_message)
{
    if (!status_dict) return;
    plist_t filedict = plist_new_dict();
    plist_dict_set_item(filedict, "DLFileErrorString", plist_new_string(error_message));
    plist_dict_set_item(filedict, "DLFileErrorCode", plist_new_uint(error_code));
    plist_dict_set_item(status_dict, path, filedict);
}

/*
 * errno 转 苹果errcode
*/
int FileToolsBackUp::errno_to_device_error(int errno_value)
{
    switch (errno_value) {
    case ENOENT:
        return -6;
    case EEXIST:
        return -7;
    case ENOTDIR:
        return -8;
    case EISDIR:
        return -9;
    case ELOOP:
        return -10;
    case EIO:
        return -11;
    case ENOSPC:
        return -15;
    default:
        return -1;
    }
}

/*
 * 处理文件的下载？
*/
int FileToolsBackUp::mb2_handle_send_file(mobilebackup2_client_t mobilebackup2, const char *backup_dir, const char *path, plist_t *errplist)
{
    uint32_t nlen = 0;
    uint32_t pathlen = strlen(path);
    uint32_t bytes = 0;
    char *localfile = string_build_path(backup_dir, path, NULL);
    char buf[32768];
#ifdef WIN32
    struct _stati64 fst;
#else
    struct stat fst;
#endif

    FILE *f = NULL;
    uint32_t slen = 0;
    int errcode = -1;
    int result = -1;
    uint32_t length;
#ifdef WIN32
    uint64_t total;
    uint64_t sent;
#else
    off_t total;
    off_t sent;
#endif

    mobilebackup2_error_t err;
    char *format_size;

    /* send path length */
    nlen = htobe32(pathlen);
    err = mobilebackup2_send_raw(mobilebackup2, (const char*)&nlen, sizeof(nlen), &bytes);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        goto leave_proto_err;
    }
    if (bytes != (uint32_t)sizeof(nlen)) {
        err = MOBILEBACKUP2_E_MUX_ERROR;
        goto leave_proto_err;
    }

    /* send path */
    err = mobilebackup2_send_raw(mobilebackup2, path, pathlen, &bytes);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        goto leave_proto_err;
    }
    if (bytes != pathlen) {
        err = MOBILEBACKUP2_E_MUX_ERROR;
        goto leave_proto_err;
    }

#ifdef WIN32
    if (_stati64(localfile, &fst) < 0)
#else
    if (stat(localfile, &fst) < 0)
#endif
    {
        if (errno != ENOENT)
            printf("%s: stat failed on '%s': %d\n", __func__, localfile, errno);
        errcode = errno;
        goto leave;
    }

    total = fst.st_size;

    format_size = string_format_size(total);
    PRINT_VERBOSE(1, "Sending '%s' (%s)\n", path, format_size);
    free(format_size);

    if (total == 0) {
        errcode = 0;
        goto leave;
    }

    f = fopen(localfile, "rb");
    if (!f) {
        printf("%s: Error opening local file '%s': %d\n", __func__, localfile, errno);
        errcode = errno;
        goto leave;
    }

    sent = 0;
    do {
        length = ((total-sent) < (long long)sizeof(buf)) ? (uint32_t)total-sent : (uint32_t)sizeof(buf);
        /* send data size (file size + 1) */
        nlen = htobe32(length+1);
        memcpy(buf, &nlen, sizeof(nlen));
        buf[4] = CODE_FILE_DATA;
        err = mobilebackup2_send_raw(mobilebackup2, (const char*)buf, 5, &bytes);
        if (err != MOBILEBACKUP2_E_SUCCESS) {
            goto leave_proto_err;
        }
        if (bytes != 5) {
            goto leave_proto_err;
        }

        /* send file contents */
        size_t r = fread(buf, 1, sizeof(buf), f);
        if (r <= 0) {
            printf("%s: read error\n", __func__);
            errcode = errno;
            goto leave;
        }
        err = mobilebackup2_send_raw(mobilebackup2, buf, r, &bytes);
        if (err != MOBILEBACKUP2_E_SUCCESS) {
            goto leave_proto_err;
        }
        if (bytes != (uint32_t)r) {
            printf("Error: sent only %d of %d bytes\n", bytes, (int)r);
            goto leave_proto_err;
        }
        sent += r;
    } while (sent < total);
    fclose(f);
    f = NULL;
    errcode = 0;

leave:
    if (errcode == 0) {
        result = 0;
        nlen = 1;
        nlen = htobe32(nlen);
        memcpy(buf, &nlen, 4);
        buf[4] = CODE_SUCCESS;
        mobilebackup2_send_raw(mobilebackup2, buf, 5, &bytes);
    } else {
        if (!*errplist) {
            *errplist = plist_new_dict();
        }
        char *errdesc = strerror(errcode);
        mb2_multi_status_add_file_error(*errplist, path, errno_to_device_error(errcode), errdesc);

        length = strlen(errdesc);
        nlen = htobe32(length+1);
        memcpy(buf, &nlen, 4);
        buf[4] = CODE_ERROR_LOCAL;
        slen = 5;
        memcpy(buf+slen, errdesc, length);
        slen += length;
        err = mobilebackup2_send_raw(mobilebackup2, (const char*)buf, slen, &bytes);
        if (err != MOBILEBACKUP2_E_SUCCESS) {
            printf("could not send message\n");
        }
        if (bytes != slen) {
            printf("could only send %d from %d\n", bytes, slen);
        }
    }

leave_proto_err:
    if (f)
        fclose(f);
    free(localfile);
    return result;
}
void FileToolsBackUp::mb2_handle_send_files(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir)
{
    uint32_t cnt;
    uint32_t i = 0;
    uint32_t sent;
    plist_t errplist = NULL;

    if (!message || (plist_get_node_type(message) != PLIST_ARRAY) || (plist_array_get_size(message) < 2) || !backup_dir) return;

    plist_t files = plist_array_get_item(message, 1);
    cnt = plist_array_get_size(files);

    for (i = 0; i < cnt; i++) {
        plist_t val = plist_array_get_item(files, i);
        if (plist_get_node_type(val) != PLIST_STRING) {
            continue;
        }
        char *str = NULL;
        plist_get_string_val(val, &str);
        if (!str)
            continue;

        if (mb2_handle_send_file(mobilebackup2, backup_dir, str, &errplist) < 0) {
            free(str);
            //printf("Error when sending file '%s' to device\n", str);
            // TODO: perhaps we can continue, we've got a multi status response?!
            break;
        }
        free(str);
    }

    /* send terminating 0 dword */
    uint32_t zero = 0;
    mobilebackup2_send_raw(mobilebackup2, (char*)&zero, 4, &sent);

    if (!errplist) {
        plist_t emptydict = plist_new_dict();
        mobilebackup2_send_status_response(mobilebackup2, 0, NULL, emptydict);
        plist_free(emptydict);
    } else {
        mobilebackup2_send_status_response(mobilebackup2, -13, "Multi status", errplist);
        plist_free(errplist);
    }
}

/*
 * 接受文件名
*/
int FileToolsBackUp::mb2_receive_filename(mobilebackup2_client_t mobilebackup2, char** filename)
{
    uint32_t nlen = 0;
    uint32_t rlen = 0;

    do {
        nlen = 0;
        rlen = 0;
        mobilebackup2_receive_raw(mobilebackup2, (char*)&nlen, 4, &rlen);
        nlen = be32toh(nlen);

        if ((nlen == 0) && (rlen == 4)) {
            // a zero length means no more files to receive
            return 0;
        }
        if (rlen == 0) {
            // device needs more time, waiting...
            continue;
        }
        if (nlen > 4096) {
            // filename length is too large
            printf("ERROR: %s: too large filename length (%d)!\n", __func__, nlen);
            return 0;
        }

        if (*filename != NULL) {
            free(*filename);
            *filename = NULL;
        }

        *filename = (char*)malloc(nlen+1);

        rlen = 0;
        mobilebackup2_receive_raw(mobilebackup2, *filename, nlen, &rlen);
        if (rlen != nlen) {
            printf("ERROR: %s: could not read filename\n", __func__);
            return 0;
        }

        char* p = *filename;
        p[rlen] = 0;

        break;
    } while(1 && !quit_flag);

    return nlen;
}
int FileToolsBackUp::mb2_handle_receive_files(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir)
{
    uint64_t backup_real_size = 0;
    uint64_t backup_total_size = 0;
    uint32_t blocksize;
    uint32_t bdone;
    uint32_t rlen;
    uint32_t nlen = 0;
    uint32_t r;
    char buf[32768];
    char *fname = NULL;
    char *dname = NULL;
    char *bname = NULL;
    char code = 0;
    char last_code = 0;
    plist_t node = NULL;
    FILE *f = NULL;
    unsigned int file_count = 0;
    int errcode = 0;
    char *errdesc = NULL;

    if (!message || (plist_get_node_type(message) != PLIST_ARRAY) || plist_array_get_size(message) < 4 || !backup_dir) return 0;

    node = plist_array_get_item(message, 3);
    if (plist_get_node_type(node) == PLIST_UINT) {
        plist_get_uint_val(node, &backup_total_size);
    }
    if (backup_total_size > 0) {
        PRINT_VERBOSE(1, "Receiving files\n");
    }

    do {
        if (quit_flag)
            break;

        nlen = mb2_receive_filename(mobilebackup2, &dname);
        if (nlen == 0) {
            break;
        }

        nlen = mb2_receive_filename(mobilebackup2, &fname);
        if (!nlen) {
            break;
        }

        if (bname != NULL) {
            free(bname);
            bname = NULL;
        }

        bname = string_build_path(backup_dir, fname, NULL);

        if (fname != NULL) {
            free(fname);
            fname = NULL;
        }

        r = 0;
        nlen = 0;
        mobilebackup2_receive_raw(mobilebackup2, (char*)&nlen, 4, &r);
        if (r != 4) {
            printf("ERROR: %s: could not receive code length!\n", __func__);
            break;
        }
        nlen = be32toh(nlen);

        last_code = code;
        code = 0;

        mobilebackup2_receive_raw(mobilebackup2, &code, 1, &r);
        if (r != 1) {
            printf("ERROR: %s: could not receive code!\n", __func__);
            break;
        }

        /* TODO remove this */
        if ((code != CODE_SUCCESS) && (code != CODE_FILE_DATA) && (code != CODE_ERROR_REMOTE)) {
            PRINT_VERBOSE(1, "Found new flag %02x\n", code);
        }

        OsUtils::osRemoveFile(bname);
        f = fopen(bname, "wb");
        while (f && (code == CODE_FILE_DATA)) {
            blocksize = nlen-1;
            bdone = 0;
            rlen = 0;
            while (bdone < blocksize) {
                if ((blocksize - bdone) < sizeof(buf)) {
                    rlen = blocksize - bdone;
                } else {
                    rlen = sizeof(buf);
                }
                mobilebackup2_receive_raw(mobilebackup2, buf, rlen, &r);
                if ((int)r <= 0) {
                    break;
                }
                fwrite(buf, 1, r, f);
                bdone += r;
            }
            if (bdone == blocksize) {
                backup_real_size += blocksize;
            }
            if (backup_total_size > 0) {
                print_progress(backup_real_size, backup_total_size);
            }
            if (quit_flag)
                break;
            nlen = 0;
            mobilebackup2_receive_raw(mobilebackup2, (char*)&nlen, 4, &r);
            nlen = be32toh(nlen);
            if (nlen > 0) {
                last_code = code;
                mobilebackup2_receive_raw(mobilebackup2, &code, 1, &r);
            } else {
                break;
            }
        }
        if (f) {
            fclose(f);
            file_count++;
        } else {
            errcode = errno_to_device_error(errno);
            errdesc = strerror(errno);
            printf("Error opening '%s' for writing: %s\n", bname, errdesc);
            break;
        }
        if (nlen == 0) {
            break;
        }

        /* check if an error message was received */
        if (code == CODE_ERROR_REMOTE) {
            /* error message */
            char *msg = (char*)malloc(nlen);
            mobilebackup2_receive_raw(mobilebackup2, msg, nlen-1, &r);
            msg[r] = 0;
            /* If sent using CODE_FILE_DATA, end marker will be CODE_ERROR_REMOTE which is not an error! */
            if (last_code != CODE_FILE_DATA) {
                fprintf(stdout, "\nReceived an error message from device: %s\n", msg);
            }
            free(msg);
        }
    } while (1);

    if (fname != NULL)
        free(fname);

    /* if there are leftovers to read, finish up cleanly */
    if ((int)nlen-1 > 0) {
        PRINT_VERBOSE(1, "\nDiscarding current data hunk.\n");
        fname = (char*)malloc(nlen-1);
        mobilebackup2_receive_raw(mobilebackup2, fname, nlen-1, &r);
        free(fname);
        OsUtils::osRemoveFile(bname);
    }

    /* clean up */
    if (bname != NULL)
        free(bname);

    if (dname != NULL)
        free(dname);

    plist_t empty_plist = plist_new_dict();
    mobilebackup2_send_status_response(mobilebackup2, errcode, errdesc, empty_plist);
    plist_free(empty_plist);

    return file_count;
}

/*
 * 处理目录列表？
*/
void FileToolsBackUp::mb2_handle_list_directory(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir)
{
    if (!message || (plist_get_node_type(message) != PLIST_ARRAY) || plist_array_get_size(message) < 2 || !backup_dir) return;

    plist_t node = plist_array_get_item(message, 1);
    char *str = NULL;
    if (plist_get_node_type(node) == PLIST_STRING) {
        plist_get_string_val(node, &str);
    }
    if (!str) {
        printf("ERROR: Malformed DLContentsOfDirectory message\n");
        // TODO error handling
        return;
    }

    char *path = string_build_path(backup_dir, str, NULL);
    free(str);

    plist_t dirlist = plist_new_dict();

    DIR* cur_dir = opendir(path);
    if (cur_dir) {
        struct dirent* ep;
        while ((ep = readdir(cur_dir))) {
            if ((strcmp(ep->d_name, ".") == 0) || (strcmp(ep->d_name, "..") == 0)) {
                continue;
            }
            char *fpath = string_build_path(path, ep->d_name, NULL);
            if (fpath) {
                plist_t fdict = plist_new_dict();
                struct stat st;
                stat(fpath, &st);
                const char *ftype = "DLFileTypeUnknown";
                if (S_ISDIR(st.st_mode)) {
                    ftype = "DLFileTypeDirectory";
                } else if (S_ISREG(st.st_mode)) {
                    ftype = "DLFileTypeRegular";
                }
                plist_dict_set_item(fdict, "DLFileType", plist_new_string(ftype));
                plist_dict_set_item(fdict, "DLFileSize", plist_new_uint(st.st_size));
                plist_dict_set_item(fdict, "DLFileModificationDate",
                                    plist_new_date(st.st_mtime - MAC_EPOCH, 0));

                plist_dict_set_item(dirlist, ep->d_name, fdict);
                free(fpath);
            }
        }
        closedir(cur_dir);
    }
    free(path);

    /* TODO error handling */
    mobilebackup2_error_t err = mobilebackup2_send_status_response(mobilebackup2, 0, NULL, dirlist);
    plist_free(dirlist);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
}

/*
 * 生成目录
*/
void FileToolsBackUp::mb2_handle_make_directory(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir)
{
    if (!message || (plist_get_node_type(message) != PLIST_ARRAY) || plist_array_get_size(message) < 2 || !backup_dir) return;

    plist_t dir = plist_array_get_item(message, 1);
    char *str = NULL;
    int errcode = 0;
    char *errdesc = NULL;
    plist_get_string_val(dir, &str);

    char *newpath = string_build_path(backup_dir, str, NULL);
    free(str);

    if (OsUtils::osMkdirWithParents(newpath, 0755) < 0) {
        errdesc = strerror(errno);
        if (errno != EEXIST) {
            printf("mkdir: %s (%d)\n", errdesc, errno);
        }
        errcode = errno_to_device_error(errno);
    }
    free(newpath);
    mobilebackup2_error_t err = mobilebackup2_send_status_response(mobilebackup2, errcode, errdesc, NULL);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
}

/*
 * 拷贝文件
*/
void FileToolsBackUp::mb2_copy_file_by_path(const char *src, const char *dst)
{
    FILE *from, *to;
    char buf[BUFSIZ];
    size_t length;

    /* open source file */
    if ((from = fopen(src, "rb")) == NULL) {
        printf("Cannot open source path '%s'.\n", src);
        return;
    }

    /* open destination file */
    if ((to = fopen(dst, "wb")) == NULL) {
        printf("Cannot open destination file '%s'.\n", dst);
        fclose(from);
        return;
    }

    /* copy the file */
    while ((length = fread(buf, 1, BUFSIZ, from)) != 0) {
        fwrite(buf, 1, length, to);
    }

    if(fclose(from) == EOF) {
        printf("Error closing source file.\n");
    }

    if(fclose(to) == EOF) {
        printf("Error closing destination file.\n");
    }
}

/*
 * 拷贝目录
*/
void FileToolsBackUp::mb2_copy_directory_by_path(const char *src, const char *dst)
{
    if (!src || !dst) {
        return;
    }

    struct stat st;

    /* if src does not exist */
    if ((stat(src, &st) < 0) || !S_ISDIR(st.st_mode)) {
        printf("ERROR: Source directory does not exist '%s': %s (%d)\n", src, strerror(errno), errno);
        return;
    }

    /* if dst directory does not exist */
    if ((stat(dst, &st) < 0) || !S_ISDIR(st.st_mode)) {
        /* create it */
        if (OsUtils::osMkdirWithParents(dst, 0755) < 0) {
            printf("ERROR: Unable to create destination directory '%s': %s (%d)\n", dst, strerror(errno), errno);
            return;
        }
    }

    /* loop over src directory contents */
    DIR *cur_dir = opendir(src);
    if (cur_dir) {
        struct dirent* ep;
        while ((ep = readdir(cur_dir))) {
            if ((strcmp(ep->d_name, ".") == 0) || (strcmp(ep->d_name, "..") == 0)) {
                continue;
            }
            char *srcpath = string_build_path(src, ep->d_name, NULL);
            char *dstpath = string_build_path(dst, ep->d_name, NULL);
            if (srcpath && dstpath) {
                /* copy file */
                mb2_copy_file_by_path(srcpath, dstpath);
            }

            if (srcpath)
                free(srcpath);
            if (dstpath)
                free(dstpath);
        }
        closedir(cur_dir);
    }
}

/**
 * signal handler function for cleaning up properly
 */
void FileToolsBackUp::clean_exit(int sig)
{
    fprintf(stderr, "Exiting...\n");
    quit_flag++;
}


