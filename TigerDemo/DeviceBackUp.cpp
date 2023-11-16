#include "DeviceBackUp.h"

#include <QDir>
#include <QStorageInfo>
#include <QString>
#include "FileToolsBackUp.h"
#include "OsUtils.h"

//#include <Windows.h>
//#include <stdio.h>
//#include <string.h>
//#include <errno.h>
//#include <stdlib.h>
//#include <signal.h>
//#include <unistd.h>
//#include <dirent.h>
//#include <libgen.h>
//#include <ctype.h>
//#include <time.h>
//#include <getopt.h>
//#include <libimobiledevice/libimobiledevice.h>
//#include <libimobiledevice/lockdown.h>
//#include <libimobiledevice/mobilebackup2.h>
//#include <libimobiledevice/notification_proxy.h>
//#include <libimobiledevice/afc.h>
//#include <libimobiledevice/installation_proxy.h>
//#include <libimobiledevice/sbservices.h>
//#include <libimobiledevice/diagnostics_relay.h>
#include <plist/plist.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <libimobiledevice-glue/utils.h>
#ifdef __cplusplus
}
#endif

#define TOOL_NAME "DeviceBackup"
#define LOCK_ATTEMPTS 50
#define LOCK_WAIT 200000

DeviceBackUp::DeviceBackUp(QObject *parent)
    : QObject{parent}
{

}

void DeviceBackUp::start()
{
    if(m_thread){
        emit displayWarningDialog("Bakcup", "The backup is in progress. Please wait or stop the current backup.");
    } else{
        // 初始化控制变量
        m_quitFlag = false; // 结束标志

        m_thread = new std::thread(&DeviceBackUp::backupThreadCallBack, this);
    }
}

void DeviceBackUp::stop()
{
    if(m_thread){
        m_quitFlag = true;
        m_thread->join();
        emit backupCompleted();
    }
}

bool DeviceBackUp::init()
{
    // 重置进度条和变量
    emit setProgressBar(0);
    initVar();

    // 初始化过程中，外部或内部因素会使得备份提前结束
    // 所以每次我们都判断一下，也提前退出
    if(m_quitFlag || !connectDevice())
        return false;
    if(m_quitFlag || !connectLockdownd())
        return false;
    if(m_quitFlag || !connectNp())
        return false;
    if(m_quitFlag || !connectMobilBp2())
        return false;
    if(m_quitFlag || !exchangeVersion())
        return false;
    if(m_quitFlag || !connectAFC())
        return false;
    if(m_quitFlag || !lockAFCFile())
        return false;


    return true;
}

void DeviceBackUp::initVar()
{
    m_forceFullBackup = true;
    m_willEncrypt = false;
    m_quitFlag = false;
    m_progress_finished = false;
     m_overall_progress = 0.0f;
    // //
    m_backupErrCode = 0;
    result_code = -1;
    file_count = 0;
}

void DeviceBackUp::clear()
{
    // device, lockdownd, np, afc, lockFile, mbp2
    // 后构造的先释放
    m_mobilebackup2.closeMbp2();
    if(m_lockfile){
        m_afc.lockFile(m_lockfile, AFC_LOCK_UN);
        m_afc.closeFile(m_lockfile);
        m_lockfile = (uint64_t)0;
    }
    m_afc.closeAFC();
    m_notificationProxy.closeNp();
    m_lockdown.closeLockdownd();
    m_device.closeIdevice();
    // 重置变量：在备份服务执行时进行重置，即开始时重置，结束时不重置

    // 线程分离, 本次任务正常完成，主线程不再需要关心该线程
    if(m_progress_finished) {
        m_thread->detach();
    }
    // 外部因素会join，则主线程会阻塞到该线程退出；
    // 内部因素，该线程会比主线程早退出
    m_thread = nullptr;
}

void DeviceBackUp::backupThreadCallBack()
{

    // 初始化和请求过程前，先判断是否已经终止
    // 执行初始化函数：构造一系列对象
    if(m_quitFlag || !init())
    {
        // 清理
        emit logShow("\n\r\r\rInitialization failed.\n");
        clear();
        return ;
    }
    // 请求备份
    if(m_quitFlag || !sendBackupRequest())
    {
        // 清理
        emit logShow("\n\r\r\rBackup request failed.\n");
        clear();
        return ;
    }
    // 处理消息
    messageLoop();
    // 打印结果
    if(m_progress_finished) {
        emit logShow("Backup successful.");
    } else {
        emit logShow("Backup failed.");
    }
    // 清理
    clear();

}

bool DeviceBackUp::connectDevice()
{
    emit logShow("Connecting to the device.");

    if(IDEVICE_E_SUCCESS == m_device.openIdevice()){
        m_udid = m_device.getUdid();
        m_device.closeIdevice();
    }else {
        emit logShow("\n\r\r\rConnecting to the device.\n");
        return false;
    }

    auto ret = m_device.openIdeviceWithOptions(m_udid, IDEVICE_LOOKUP_USBMUX);
    if(IDEVICE_E_SUCCESS != ret){
        emit logShow("\n\r\r\rConnecting to the device.\n");
        return false;
    }

    return true;
}

bool DeviceBackUp::connectLockdownd()
{
    emit logShow("Connecting to the lockdownd service.");
    auto ret = m_lockdown.openLockdowndWithHandshake(m_device);
    if(LOCKDOWN_E_SUCCESS != ret) {
        emit logShow("Failed to connect to the lockdownd service");
        return false;
    }
    return true;
}

bool DeviceBackUp::connectNp()
{
    emit logShow("Connecting to the NP service.");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startService(NP_SERVICE_NAME,&service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        m_notificationProxy.openNp(m_device,service);
        m_notificationProxy.observeNotifications();
        lockdownd_service_descriptor_free(service);
        return true;
    } else{
        emit logShow("\n\r\r\rFailed to connect to the NP service.\n");
        return false;
    }
}

bool DeviceBackUp::connectAFC()
{
    emit logShow("Connecting to the AFC service.");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startService(AFC_SERVICE_NAME, &service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service->port) {
        m_afc.openAFC(m_device,service);
        lockdownd_service_descriptor_free(service);
        return true;
    } else {
        emit logShow("\n\r\r\rFailed to connect to the AFC service.\n");
        return false;
    }
}

bool DeviceBackUp::lockAFCFile()
{
    // 通知
    // 打开文件
    // 加锁独占

    emit logShow("Locking AFC-related files.");
    afc_error_t aerr;
    bool success = true;
    m_notificationProxy.postNotifications(NP_SYNC_WILL_START);// 通知
    m_afc.openFile("/com.apple.itunes.lock_sync", AFC_FOPEN_RW, &m_lockfile); // 打开
    if (m_lockfile) {
        m_notificationProxy.postNotifications(NP_SYNC_LOCK_REQUEST);
        for (int i = 0; i < LOCK_ATTEMPTS && !m_quitFlag; i++) {
            aerr = m_afc.lockFile(m_lockfile, AFC_LOCK_EX);
            if (aerr == AFC_E_SUCCESS) {
                m_notificationProxy.postNotifications(NP_SYNC_DID_START);
                success = true;
                break;
            } else if (aerr == AFC_E_OP_WOULD_BLOCK) {
                std::this_thread::sleep_for(std::chrono::microseconds(LOCK_WAIT)); // 暂停等待
                continue;
            } else {
                break;
            }
        }
        if (!success) {
            m_afc.closeFile(m_lockfile);
            m_lockfile = 0;
            emit logShow("\n\r\r\rLocking AFC-related files.\n");
            return false;
        }
    }
    return true;
}

bool DeviceBackUp::connectMobilBp2()
{
    emit logShow("Connecting to the backup2 service.");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startServiceWithEscrowBag(MOBILEBACKUP2_SERVICE_NAME, &service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        QString tmp;
//        tmp.sprintf("\"%s\" service on port %d.", MOBILEBACKUP2_SERVICE_NAME, service->port);
        tmp = QString("%1 service on port %2.").arg(MOBILEBACKUP2_SERVICE_NAME).arg(service->port);
        emit logShow(tmp);
        m_mobilebackup2.openMbp2(m_device,service);
        lockdownd_service_descriptor_free(service);
        return true;
    } else  {
        emit logShow("\n\r\r\rFailed to connect to the backup2 service.\n");
        return false;
    }
}

bool DeviceBackUp::exchangeVersion()
{
    emit logShow("Exchanging version information.");
    double local_versions[2] = {2.0, 2.1};
    double remote_version = 0.0;
    err = m_mobilebackup2.versionExchange(local_versions, 2, &remote_version);
    if (MOBILEBACKUP2_E_SUCCESS != err) {
        emit logShow("\n\r\r\rFailed to exchange version information.\n");
        return false;
    }
    return true;
}

bool DeviceBackUp::sendBackupRequest(bool isFullBackup)
{
    emit logShow("Requesting backup.");

    plist_t opts = plist_new_dict(); // 属性节点
    if (isFullBackup) {
        emit logShow("ForceFullBackup.");
        plist_dict_set_item(opts,"ForceFullBackup",plist_new_bool(1));
    }
    if (m_willEncrypt) {
        emit logShow("Encrypted backup.");
    } else {
        emit logShow("Unencrypted backup.");
    }
    auto err = m_mobilebackup2.sendRequest("Backup", m_udid.toUtf8(), m_udid.toUtf8(), opts);
    if (opts) {
        plist_free(opts);
    }
    if (MOBILEBACKUP2_E_SUCCESS != err) {
        emit logShow("\n\r\r\rForceFullBackup.\n");
        return false;
    }
    return true;
}

void DeviceBackUp::messageLoop()
{
    char *dlmsg = NULL;
    plist_t message = nullptr;
    // 异常退出 或 正常结束
    while(!m_quitFlag)
    {
        dlmsg = nullptr;
        message = nullptr;
        // 获取消息
        mobilebackup2_error_t mberr = m_mobilebackup2.receiveMessage(&message, &dlmsg);
        if (mberr == MOBILEBACKUP2_E_RECEIVE_TIMEOUT) { // 无
            emit logShow("Waiting...");
            continue;
        } else if (mberr != MOBILEBACKUP2_E_SUCCESS) { // 获取失败
            emit logShow("\n\r\r\rFailed to read the message.\n");
            break;
        }
        // 处理消息
        bool handleRet = handleMessageOne(message, dlmsg);
        free(dlmsg);
        free(message);
        if(!handleRet){
            // 因为收到progressMessage一定会返回假，则该循环一定会结束
            break;
        }
    }

}

bool DeviceBackUp::handleMessageOne(plist_t message, const char* dlmsg)
{
    //1. 打印进度：先获取再打印
    setAndPrintOverallProgress(message, dlmsg);
    //2. 执行任务：先匹配再执行
    if (!strcmp(dlmsg, "DLMessageDownloadFiles")) {
        /* device wants to download files from the computer */
        return downloadFiles(message);
    } else if (!strcmp(dlmsg, "DLMessageUploadFiles")) {
        /* device wants to send files to the computer */
        return uploadFiles(message);
    } else if (!strcmp(dlmsg, "DLMessageGetFreeDiskSpace")) {
        /* device wants to know how much disk space is available on the computer */
        return getFreeDiskSpace(message);
    } else if (!strcmp(dlmsg, "DLMessagePurgeDiskSpace")) {
        /* device wants to purge disk space on the host - not supported */
        return purgeDiskSpace(message);
    } else if (!strcmp(dlmsg, "DLContentsOfDirectory")) {
        /* list directory contents */
        return contentsOfDirectory(message);
    } else if (!strcmp(dlmsg, "DLMessageCreateDirectory")) {
        /* make a directory */
        return createDirectory(message);
    } else if (!strcmp(dlmsg, "DLMessageMoveFiles") || !strcmp(dlmsg, "DLMessageMoveItems")) {
        /* perform a series of rename operations */
        return moveFilesAndItems(message);
    } else if (!strcmp(dlmsg, "DLMessageRemoveFiles") || !strcmp(dlmsg, "DLMessageRemoveItems")) {
        /* perform a series of remove operations */
        return removeFilesAndItems(message);
    } else if (!strcmp(dlmsg, "DLMessageCopyItem")) {
        /* perform a series of copy operations */
        return copyItem(message);
    } else if (!strcmp(dlmsg, "DLMessageDisconnect")) {
        /* break message loop if device is disconnected. */
        disconnect(message);
        return false;
    } else if (!strcmp(dlmsg, "DLMessageProcessMessage")) {
        /* process message and break the backup message loop */
        processMessage(message);
        return false;
    }
    return true;

    return 0;
}

bool DeviceBackUp::downloadFiles(plist_t message)
{
    emit logShow("downloadFiles!!!!!!!!!!!!!");
    FileToolsBackUp::mb2_handle_send_files(m_mobilebackup2.getMbp2(), message, m_backupPath.toUtf8().constData());
    return true;
}

bool DeviceBackUp::uploadFiles(plist_t message)
{
    emit logShow("uploadFiles!!!!!!!!!!!!!");
    file_count += FileToolsBackUp::mb2_handle_receive_files(m_mobilebackup2.getMbp2(), message, m_backupPath.toUtf8().constData());
    return true;
}

bool DeviceBackUp::getFreeDiskSpace(plist_t message)
{
    emit logShow("getFreeDiskSpace!!!!!!!!!!!!!");
    uint64_t freespace = 0;
    int res = -1;
    QStorageInfo storageInfo = QStorageInfo::root();
//    if(freespace = storageInfo.bytesAvailable()) {
//        res = 0;
//    }
    if (GetDiskFreeSpaceExA(m_backupPath.toUtf8().constData(), (PULARGE_INTEGER)&freespace, NULL, NULL)) {
        res = 0;
    }
    plist_t freespace_item = plist_new_uint(freespace);
    mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), res, NULL, freespace_item);
    plist_free(freespace_item);
    return true;
}

bool DeviceBackUp::purgeDiskSpace(plist_t message)
{
    emit logShow("purgeDiskSpace!!!!!!!!!!!!!");
    plist_t empty_dict = plist_new_dict();
    err = mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), -1, "Operation not supported", empty_dict);
    plist_free(empty_dict);
    return true;
}

bool DeviceBackUp::contentsOfDirectory(plist_t message)
{
    emit logShow("contentsOfDirectory!!!!!!!!!!!!!");
    FileToolsBackUp::mb2_handle_list_directory(m_mobilebackup2.getMbp2(), message, m_backupPath.toUtf8().constData());
    return true;
}

bool DeviceBackUp::createDirectory(plist_t message)
{
    emit logShow("创建目录!!!!!!!!!!!!!");
    if (!message || (plist_get_node_type(message) != PLIST_ARRAY) || plist_array_get_size(message) < 2 || !backup_dir)
        return false;

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
        errcode = FileToolsBackUp::errno_to_device_error(errno);
    }
    free(newpath);
    mobilebackup2_error_t err = mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), errcode, errdesc, NULL);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
    return true;
}

bool DeviceBackUp::moveFilesAndItems(plist_t message)
{
    emit logShow("移动文件!!!!!!!!!!!!!");
    plist_t moves = plist_array_get_item(message, 1);
    uint32_t cnt = plist_dict_get_size(moves);
//    PRINT_VERBOSE(1, "Moving %d file%s\n", cnt, (cnt == 1) ? "" : "s");
    plist_dict_iter iter = NULL;
    plist_dict_new_iter(moves, &iter);
    errcode = 0;
    errdesc = NULL;
    if (iter) {
        char *key = NULL;
        plist_t val = NULL;
        do {
            plist_dict_next_item(moves, iter, &key, &val);
            if (key && (plist_get_node_type(val) == PLIST_STRING)) {
                char *str = NULL;
                plist_get_string_val(val, &str);
                if (str) {


                    char *newpath = string_build_path(backup_dir, str, NULL);
                    free(str);
                    char *oldpath = string_build_path(backup_dir, key, NULL);

                    if ((stat(newpath, &st) == 0) && S_ISDIR(st.st_mode))
                        OsUtils::osRemoveDirRecursively(newpath);
                    //rmdir_recursive(newpath);
                    else
                        OsUtils::osRemoveFile(newpath);
                    //remove_file(newpath);
                    if (OsUtils::osRename(oldpath, newpath) < 0) {
                        printf("Renameing '%s' to '%s' failed: %s (%d)\n", oldpath, newpath, strerror(errno), errno);
                        errcode = FileToolsBackUp::errno_to_device_error(-1);
                        errdesc = strerror(-1);
                        break;
                    }
                    free(oldpath);
                    free(newpath);
                }
                free(key);
                key = NULL;
            }
        } while (val);
        free(iter);
    } else {
        errcode = -1;
        errdesc = "Could not create dict iterator";
        printf("Could not create dict iterator\n");
    }
    plist_t empty_dict = plist_new_dict();
    mobilebackup2_error_t err = mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), errcode, errdesc, empty_dict);
    plist_free(empty_dict);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
    return true;
}

bool DeviceBackUp::removeFilesAndItems(plist_t message)
{
    emit logShow("删除文件!!!!!!!!!!!!!");
    plist_t removes = plist_array_get_item(message, 1);
    uint32_t cnt = plist_array_get_size(removes);
//    PRINT_VERBOSE(1, "Removing %d file%s\n", cnt, (cnt == 1) ? "" : "s");
    uint32_t ii = 0;
    errcode = 0;
    errdesc = NULL;
    for (ii = 0; ii < cnt; ii++) {
        plist_t val = plist_array_get_item(removes, ii);
        if (plist_get_node_type(val) == PLIST_STRING) {
            char *str = NULL;
            plist_get_string_val(val, &str);
            if (str) {
                const char *checkfile = strchr(str, '/');
                int suppress_warning = 0;
                if (checkfile) {
                    if (strcmp(checkfile+1, "Manifest.mbdx") == 0) {
                        suppress_warning = 1;
                    }
                }
                char *newpath = string_build_path(backup_dir, str, NULL);
                free(str);
                int res = 0;
                if ((stat(newpath, &st) == 0) && S_ISDIR(st.st_mode)) {
                    res = OsUtils::osRemoveDirRecursively(newpath);
                } else {
                    res = OsUtils::osRemoveFile(newpath);
                }
                if (res != 0 && res != ENOENT) {
                    if (!suppress_warning)
                        printf("Could not remove '%s': %s (%d)\n", newpath, strerror(res), res);
                    errcode = FileToolsBackUp::errno_to_device_error(res);
                    errdesc = strerror(res);
                }
                free(newpath);
            }
        }
    }
    plist_t empty_dict = plist_new_dict();
    err = mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), errcode, errdesc, empty_dict);
    plist_free(empty_dict);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
    return true;
}

bool DeviceBackUp::copyItem(plist_t message)
{
    emit logShow("复制项目!!!!!!!!!!!!!");
    plist_t srcpath = plist_array_get_item(message, 1);
    plist_t dstpath = plist_array_get_item(message, 2);
    errcode = 0;
    errdesc = NULL;
    if ((plist_get_node_type(srcpath) == PLIST_STRING) && (plist_get_node_type(dstpath) == PLIST_STRING)) {
        char *src = NULL;
        char *dst = NULL;
        plist_get_string_val(srcpath, &src);
        plist_get_string_val(dstpath, &dst);
        if (src && dst) {
            char *oldpath = string_build_path(backup_dir, src, NULL);
            char *newpath = string_build_path(backup_dir, dst, NULL);

//            PRINT_VERBOSE(1, "Copying '%s' to '%s'\n", src, dst);

            /* check that src exists */
            if ((stat(oldpath, &st) == 0) && S_ISDIR(st.st_mode)) {
                FileToolsBackUp::mb2_copy_directory_by_path(oldpath, newpath);
            } else if ((stat(oldpath, &st) == 0) && S_ISREG(st.st_mode)) {
                FileToolsBackUp::mb2_copy_file_by_path(oldpath, newpath);
            }

            free(newpath);
            free(oldpath);
        }
        free(src);
        free(dst);
    }
    plist_t empty_dict = plist_new_dict();
    err = mobilebackup2_send_status_response(m_mobilebackup2.getMbp2(), errcode, errdesc, empty_dict);
    plist_free(empty_dict);
    if (err != MOBILEBACKUP2_E_SUCCESS) {
        printf("Could not send status response, error %d\n", err);
    }
    return true;
}

bool DeviceBackUp::disconnect(plist_t message)
{
    emit logShow("断开连接!!!!!!!!!!!!!");
    return true;
}

bool DeviceBackUp::processMessage(plist_t message)
{
    emit logShow("处理消息!!!!!!!!!!!!!");
    node_tmp = plist_array_get_item(message, 1);
    if (plist_get_node_type(node_tmp) != PLIST_DICT) {
        printf("Unknown message received!\n");
    }
    plist_t nn;
    int error_code = -1;
    int operation_ok = 0;
    nn = plist_dict_get_item(node_tmp, "ErrorCode");
    if (nn && (plist_get_node_type(nn) == PLIST_UINT)) {
        uint64_t ec = 0;
        plist_get_uint_val(nn, &ec);
        error_code = (uint32_t)ec;
        if (error_code == 0) {
            operation_ok = 1;
            result_code = 0;
        } else {
            result_code = -error_code;
        }
    }
    nn = plist_dict_get_item(node_tmp, "ErrorDescription");
    char *str = NULL;
    if (nn && (plist_get_node_type(nn) == PLIST_STRING)) {
        plist_get_string_val(nn, &str);
    }
    if (error_code != 0) {
        if (str) {
            printf("ErrorCode %d: %s\n", error_code, str);
        } else {
            printf("ErrorCode %d: (Unknown)\n", error_code);
        }
    }
    if (str) {
        free(str);
    }
    nn = plist_dict_get_item(node_tmp, "Content");
    if (nn && (plist_get_node_type(nn) == PLIST_STRING)) {
        str = NULL;
        plist_get_string_val(nn, &str);
//        PRINT_VERBOSE(1, "Content:\n");
        printf("%s", str);
        free(str);
    }
    return true;
}

void DeviceBackUp::setAndPrintOverallProgress(plist_t message, const char * dlmsg)
{
    plist_t node = NULL;
    double progress = 0.0;

    // 下载、上传、删除、移动
    if (!strcmp(dlmsg, "DLMessageDownloadFiles")) {
        node = plist_array_get_item(message, 3);
    } else if (!strcmp(dlmsg, "DLMessageUploadFiles")) {
        node = plist_array_get_item(message, 2);
    } else if (!strcmp(dlmsg, "DLMessageMoveFiles") || !strcmp(dlmsg, "DLMessageMoveItems")) {
        node = plist_array_get_item(message, 3);
    } else if (!strcmp(dlmsg, "DLMessageRemoveFiles") || !strcmp(dlmsg, "DLMessageRemoveItems")) {
        node = plist_array_get_item(message, 3);
    }
    if (node != NULL) {
        plist_get_real_val(node, &progress);
        if (progress > 0.0) {
            m_overall_progress = progress;
            emit setProgressBar(m_overall_progress);
            if(m_overall_progress >= 100.0f){
                m_progress_finished = true;
            }
        }
    }

}
