#include "IdeviceBackUp.h"
#include "OsUtils.h"
#include "FileToolsBackUp.h"

IdeviceBackUp::IdeviceBackUp(QWidget *parent)
    : QWidget{parent}
{
    connect(this, &IdeviceBackUp::clearBackup, this, &IdeviceBackUp::stop);
}

void IdeviceBackUp::freeBackUpVar()
{
    if (lockdown) {
        lockdownd_client_free(lockdown);
        lockdown = NULL;
    }

    if (mobilebackup2) {
        mobilebackup2_client_free(mobilebackup2);
        mobilebackup2 = NULL;
    }

    if (afc) {
        afc_client_free(afc);
        afc = NULL;
    }

    if (np) {
        np_client_free(np);
        np = NULL;
    }

    idevice_free(device);
    device = NULL;

    if (backup_password) {
        free(backup_password);
    }

    if (udid) {
        free(udid);
        udid = NULL;
    }
    if (source_udid) {
        free(source_udid);
        source_udid = NULL;
    }

    emit clearBackup();
}


void IdeviceBackUp::BackUp()
{


    /*
     * 我们需要在运行备份和恢复操作时进行优雅的退出，否则可能会造成混乱。
     * we need to exit cleanly on running backups and restores or we cause havok
    */
    signal(SIGINT, FileToolsBackUp::clean_exit);
    signal(SIGTERM, FileToolsBackUp::clean_exit);
    // 确认是备份操作 和 指定目录
    cmd = 0;

    // 创建device对象
    ret = idevice_new_with_options(&device, udid, (use_network) ? IDEVICE_LOOKUP_NETWORK : IDEVICE_LOOKUP_USBMUX);
    if (ret != IDEVICE_E_SUCCESS) {
        if (udid) {
            printf("No device found with udid %s.\n", udid);
        } else {
            printf("No device found.\n");
        }
        return ;
    }
    if (!udid) {
        idevice_get_udid(device, &udid);
    }
    if (!source_udid) {
        source_udid = strdup(udid);
    }

    // 生成info路径，能够自动确认是增量备份还是全量备份
    /* backup directory must contain an Info.plist */
    char *info_path = NULL; // info.plist文件的路径
    info_path = string_build_path(backup_directory, source_udid, "Info.plist", NULL);
    PRINT_VERBOSE(1, "Backup directory is \"%s\"\n", backup_directory);

    // 创建lockdownd
    if (LOCKDOWN_E_SUCCESS != (ldret = lockdownd_client_new_with_handshake(device, &lockdown, TOOL_NAME))) {
        printf("ERROR: Could not connect to lockdownd, error code %d\n", ldret);
        idevice_free(device);
        return ;
    }

    // 产品版本
    /* get ProductVersion */
    char *product_version = NULL;
    node_tmp = NULL;
    lockdownd_get_value(lockdown, NULL, "ProductVersion", &node_tmp);
    if (node_tmp) {
        if (plist_get_node_type(node_tmp) == PLIST_STRING) {
            plist_get_string_val(node_tmp, &product_version);
        }
        plist_free(node_tmp);
        node_tmp = NULL;
    }
    if (product_version) {
        int vers[3] = { 0, 0, 0 };
        if (sscanf(product_version, "%d.%d.%d", &vers[0], &vers[1], &vers[2]) >= 2) {
            DEVICE_VERSION(vers[0], vers[1], vers[2]);
        }
    }

    // 开启NP
    /* start notification_proxy */
    double local_versions[2] = {2.0, 2.1};
    double remote_version = 0.0;
    afc_error_t aerr;
    ldret = lockdownd_start_service(lockdown, NP_SERVICE_NAME, &service); // 开启
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        np_client_new(device, service, &np);
        np_set_notify_callback(np, FileToolsBackUp::notify_cb, NULL);
        const char *noties[5] = {
            NP_SYNC_CANCEL_REQUEST,
            NP_SYNC_SUSPEND_REQUEST,
            NP_SYNC_RESUME_REQUEST,
            NP_BACKUP_DOMAIN_CHANGED,
            NULL
        };
        np_observe_notifications(np, noties);
    } else {
        printf("ERROR: Could not start service %s: %s\n", NP_SERVICE_NAME, lockdownd_strerror(ldret));
        cmd = CMD_LEAVE;
        goto checkpoint;
    }
    if (service) {
        lockdownd_service_descriptor_free(service);
        service = NULL;
    }

    // 开启AFC
    if (cmd == CMD_BACKUP || cmd == CMD_RESTORE) {
        /* start AFC, we need this for the lock file */
        ldret = lockdownd_start_service(lockdown, AFC_SERVICE_NAME, &service);
        if ((ldret == LOCKDOWN_E_SUCCESS) && service->port) {
            afc_client_new(device, service, &afc);
        } else {
            printf("ERROR: Could not start service %s: %s\n", AFC_SERVICE_NAME, lockdownd_strerror(ldret));
            cmd = CMD_LEAVE;
            goto checkpoint;
        }
    }
    if (service) {
        lockdownd_service_descriptor_free(service);
        service = NULL;
    }

    // 开启备份
    /* start mobilebackup service and retrieve port */
    ldret = lockdownd_start_service_with_escrow_bag(lockdown, MOBILEBACKUP2_SERVICE_NAME, &service);
    lockdownd_client_free(lockdown);
    lockdown = NULL;
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        PRINT_VERBOSE(1, "Started \"%s\" service on port %d.\n", MOBILEBACKUP2_SERVICE_NAME, service->port);
        mobilebackup2_client_new(device, service, &mobilebackup2);
        if (service) {
            lockdownd_service_descriptor_free(service);
            service = NULL;
        }

        // 交换版本信息
        /* send Hello message */
        err = mobilebackup2_version_exchange(mobilebackup2, local_versions, 2, &remote_version);
        if (err != MOBILEBACKUP2_E_SUCCESS) {
            printf("Could not perform backup protocol version exchange, error code %d\n", err);
            cmd = CMD_LEAVE;
            goto checkpoint;
        }
        PRINT_VERBOSE(1, "Negotiated Protocol Version %.1f\n", remote_version);

        /* check abort conditions */
        if (FileToolsBackUp::quit_flag > 0) {
            PRINT_VERBOSE(1, "Aborting as requested by user...\n");
            cmd = CMD_LEAVE;
            goto checkpoint;
        }

        // 判断 还原，增量/全量
        /* verify existing Info.plist */
        if (info_path && (stat(info_path, &st) == 0) && cmd != CMD_CLOUD) {
            PRINT_VERBOSE(1, "Reading Info.plist from backup.\n");
            plist_read_from_file(info_path, &info_plist, NULL);

            if (!info_plist) {
                printf("Could not read Info.plist\n");
                is_full_backup = 1;
            }
        } else {
            if (cmd == CMD_RESTORE) {
                printf("Aborting restore. Info.plist is missing.\n");
                cmd = CMD_LEAVE;
            } else {
                is_full_backup = 1;
            }
        }

        // 打开指定文件，锁定文件
        if (cmd == CMD_BACKUP || cmd == CMD_RESTORE) {
            FileToolsBackUp::do_post_notification(device, NP_SYNC_WILL_START);
            afc_file_open(afc, "/com.apple.itunes.lock_sync", AFC_FOPEN_RW, &lockfile);
        }
        if (lockfile) {
            FileToolsBackUp::do_post_notification(device, NP_SYNC_LOCK_REQUEST);
            for (i = 0; i < LOCK_ATTEMPTS; i++) {
                aerr = afc_file_lock(afc, lockfile, AFC_LOCK_EX);
                if (aerr == AFC_E_SUCCESS) {
                    FileToolsBackUp::do_post_notification(device, NP_SYNC_DID_START);
                    break;
                }
                if (aerr == AFC_E_OP_WOULD_BLOCK) {
                    usleep(LOCK_WAIT);
                    continue;
                }

                fprintf(stderr, "ERROR: could not lock file! error code: %d\n", aerr);
                afc_file_close(afc, lockfile);
                lockfile = 0;
                cmd = CMD_LEAVE;
            }
            if (i == LOCK_ATTEMPTS) {
                fprintf(stderr, "ERROR: timeout while locking for sync\n");
                afc_file_close(afc, lockfile);
                lockfile = 0;
                cmd = CMD_LEAVE;
            }
        }

    checkpoint:
        switch(cmd) {
        case CMD_BACKUP:

            PRINT_VERBOSE(1, "Starting backup...\n");

            // 在指定目录下创建当前udid的目录
            /* make sure backup device sub-directory exists */
            char* devbackupdir = string_build_path(backup_directory, source_udid, NULL);
            OsUtils::osMkdir(devbackupdir, 0x7755);
            free(devbackupdir);

            if (strcmp(source_udid, udid) != 0) {
                /* handle different source backup directory */
                // make sure target backup device sub-directory exists
                devbackupdir = string_build_path(backup_directory, udid, NULL);
                OsUtils::osMkdir(devbackupdir, 0755);
                free(devbackupdir);

                // use Info.plist path in target backup folder */
                free(info_path);
                info_path = string_build_path(backup_directory, udid, "Info.plist", NULL);
            }

            /* re-create Info.plist (Device infos, IC-Info.sidb, photos, app_ids, iTunesPrefs) */
            if (info_plist) {
                plist_free(info_plist);
                info_plist = NULL;
            }
            info_plist = FileToolsBackUp::mobilebackup_factory_info_plist_new(udid, device, afc);
            if (!info_plist) {
                fprintf(stderr, "Failed to generate Info.plist - aborting\n");
                cmd = CMD_LEAVE;
            }
            OsUtils::osRemoveFile(info_path);
            plist_write_to_file(info_plist, info_path, PLIST_FORMAT_XML, (plist_write_options_t)0);
            free(info_path);

            plist_free(info_plist);
            info_plist = NULL;

            if (cmd_flags & CMD_FLAG_FORCE_FULL_BACKUP) {
                PRINT_VERBOSE(1, "Enforcing full backup from device.\n");
                opts = plist_new_dict();
                plist_dict_set_item(opts, "ForceFullBackup", plist_new_bool(1));
            }
            /* request backup from device with manifest from last backup */
            PRINT_VERBOSE(1, "Backup will be unencrypted.\n");

            // 正式开始*************************************************************************************
            PRINT_VERBOSE(1, "Requesting backup from device...\n");
            err = mobilebackup2_send_request(mobilebackup2, "Backup", udid, source_udid, opts);
            if (opts)
                plist_free(opts);
            if (err == MOBILEBACKUP2_E_SUCCESS) {
                if (is_full_backup) {
                    PRINT_VERBOSE(1, "Full backup mode.\n");
                }	else {
                    PRINT_VERBOSE(1, "Incremental backup mode.\n");
                }
            } else {
                if (err == MOBILEBACKUP2_E_BAD_VERSION) {
                    printf("ERROR: Could not start backup process: backup protocol version mismatch!\n");
                } else if (err == MOBILEBACKUP2_E_REPLY_NOT_OK) {
                    printf("ERROR: Could not start backup process: device refused to start the backup process.\n");
                } else {
                    printf("ERROR: Could not start backup process: unspecified error occurred\n");
                }
                cmd = CMD_LEAVE;
            }
            break;
        }

        // 开始文件操作
        if (cmd != CMD_LEAVE) {
            // 重置状态
            /* reset operation success status */
            int operation_ok = 0;
            plist_t message = NULL;

            mobilebackup2_error_t mberr;
            char *dlmsg = NULL;
            int file_count = 0;
            int errcode = 0;
            const char *errdesc = NULL;
            int progress_finished = 0;

            /* process series of DLMessage* operations */
            do {
                free(dlmsg);
                dlmsg = NULL;
                mberr = mobilebackup2_receive_message(mobilebackup2, &message, &dlmsg);
                if (mberr == MOBILEBACKUP2_E_RECEIVE_TIMEOUT) {
                    PRINT_VERBOSE(2, "Device is not ready yet, retrying...\n");
                    goto files_out;
                } else if (mberr != MOBILEBACKUP2_E_SUCCESS) {
                    PRINT_VERBOSE(0, "ERROR: Could not receive from mobilebackup2 (%d)\n", mberr);
                    FileToolsBackUp::quit_flag++;
                    goto files_out;
                }

                if (!strcmp(dlmsg, "DLMessageDownloadFiles")) {
                    /* device wants to download files from the computer */
                    FileToolsBackUp::mb2_set_overall_progress_from_message(message, dlmsg);
                    emit updateBar(FileToolsBackUp::overall_progress);
                    FileToolsBackUp::mb2_handle_send_files(mobilebackup2, message, backup_directory);
                } else if (!strcmp(dlmsg, "DLMessageUploadFiles")) {
                    /* device wants to send files to the computer */
                    FileToolsBackUp::mb2_set_overall_progress_from_message(message, dlmsg);
                    emit updateBar(FileToolsBackUp::overall_progress);
                    file_count += FileToolsBackUp::mb2_handle_receive_files(mobilebackup2, message, backup_directory);
                } else if (!strcmp(dlmsg, "DLMessageGetFreeDiskSpace")) {
                    /* device wants to know how much disk space is available on the computer */
                    uint64_t freespace = 0;
                    int res = -1;
#ifdef WIN32
                    if (GetDiskFreeSpaceExA(backup_directory, (PULARGE_INTEGER)&freespace, NULL, NULL)) {
                        res = 0;
                    }
#else
                    struct statvfs fs;
                    memset(&fs, '\0', sizeof(fs));
                    res = statvfs(backup_directory, &fs);
                    if (res == 0) {
                        freespace = (uint64_t)fs.f_bavail * (uint64_t)fs.f_bsize;
                    }
#endif
                    plist_t freespace_item = plist_new_uint(freespace);
                    mobilebackup2_send_status_response(mobilebackup2, res, NULL, freespace_item);
                    plist_free(freespace_item);
                } else if (!strcmp(dlmsg, "DLMessagePurgeDiskSpace")) {
                    /* device wants to purge disk space on the host - not supported */
                    plist_t empty_dict = plist_new_dict();
                    err = mobilebackup2_send_status_response(mobilebackup2, -1, "Operation not supported", empty_dict);
                    plist_free(empty_dict);
                } else if (!strcmp(dlmsg, "DLContentsOfDirectory")) {
                    /* list directory contents */
                    FileToolsBackUp::mb2_handle_list_directory(mobilebackup2, message, backup_directory);
                } else if (!strcmp(dlmsg, "DLMessageCreateDirectory")) {
                    /* make a directory */
                    FileToolsBackUp::mb2_handle_make_directory(mobilebackup2, message, backup_directory);
                } else if (!strcmp(dlmsg, "DLMessageMoveFiles") || !strcmp(dlmsg, "DLMessageMoveItems")) {
                    /* perform a series of rename operations */
                    FileToolsBackUp::mb2_set_overall_progress_from_message(message, dlmsg);
                    emit updateBar(FileToolsBackUp::overall_progress);
                    plist_t moves = plist_array_get_item(message, 1);
                    uint32_t cnt = plist_dict_get_size(moves);
                    PRINT_VERBOSE(1, "Moving %d file%s\n", cnt, (cnt == 1) ? "" : "s");
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
                                    char *newpath = string_build_path(backup_directory, str, NULL);
                                    free(str);
                                    char *oldpath = string_build_path(backup_directory, key, NULL);

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
                    err = mobilebackup2_send_status_response(mobilebackup2, errcode, errdesc, empty_dict);
                    plist_free(empty_dict);
                    if (err != MOBILEBACKUP2_E_SUCCESS) {
                        printf("Could not send status response, error %d\n", err);
                    }
                } else if (!strcmp(dlmsg, "DLMessageRemoveFiles") || !strcmp(dlmsg, "DLMessageRemoveItems")) {
                    FileToolsBackUp::mb2_set_overall_progress_from_message(message, dlmsg);
                    emit updateBar(FileToolsBackUp::overall_progress);
                    plist_t removes = plist_array_get_item(message, 1);
                    uint32_t cnt = plist_array_get_size(removes);
                    PRINT_VERBOSE(1, "Removing %d file%s\n", cnt, (cnt == 1) ? "" : "s");
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
                                char *newpath = string_build_path(backup_directory, str, NULL);
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
                    err = mobilebackup2_send_status_response(mobilebackup2, errcode, errdesc, empty_dict);
                    plist_free(empty_dict);
                    if (err != MOBILEBACKUP2_E_SUCCESS) {
                        printf("Could not send status response, error %d\n", err);
                    }
                } else if (!strcmp(dlmsg, "DLMessageCopyItem")) {
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
                            char *oldpath = string_build_path(backup_directory, src, NULL);
                            char *newpath = string_build_path(backup_directory, dst, NULL);

                            PRINT_VERBOSE(1, "Copying '%s' to '%s'\n", src, dst);

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
                    err = mobilebackup2_send_status_response(mobilebackup2, errcode, errdesc, empty_dict);
                    plist_free(empty_dict);
                    if (err != MOBILEBACKUP2_E_SUCCESS) {
                        printf("Could not send status response, error %d\n", err);
                    }
                } else if (!strcmp(dlmsg, "DLMessageDisconnect")) {
                    break;
                } else if (!strcmp(dlmsg, "DLMessageProcessMessage")) {
                    node_tmp = plist_array_get_item(message, 1);
                    if (plist_get_node_type(node_tmp) != PLIST_DICT) {
                        printf("Unknown message received!\n");
                    }
                    plist_t nn;
                    int error_code = -1;
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
                        PRINT_VERBOSE(1, "Content:\n");
                        printf("%s", str);
                        free(str);
                    }
                    break;
                }

                // 打印进度
                /* print status */
                if ((FileToolsBackUp::overall_progress > 0) && !progress_finished) {
                    if (FileToolsBackUp::overall_progress >= 100.0F) {
                        progress_finished = 1;
                    }
                    FileToolsBackUp::print_progress_real(FileToolsBackUp::overall_progress, 0);
                    PRINT_VERBOSE(1, " Finished\n");
                }

            files_out:
                plist_free(message);
                message = NULL;
                free(dlmsg);
                dlmsg = NULL;

                // 判断是否结束
                if (FileToolsBackUp::quit_flag > 0) {
                    break;
                }
            } while (1);
            plist_free(message);
            message = NULL;
            free(dlmsg);
            dlmsg = NULL;

            // 打印完成信息
            /* report operation status to user */
            switch (cmd) {
            case CMD_BACKUP:
                PRINT_VERBOSE(1, "Received %d files from device.\n", file_count);
                if (operation_ok && FileToolsBackUp::mb2_status_check_snapshot_state(backup_directory, udid, "finished")) {
                    PRINT_VERBOSE(1, "Backup Successful.\n");
                } else {
                    if (FileToolsBackUp::quit_flag) {
                        PRINT_VERBOSE(1, "Backup Aborted.\n");
                    } else {
                        PRINT_VERBOSE(1, "Backup Failed (Error Code %d).\n", -result_code);
                    }
                }
                break;
            case CMD_LEAVE:
            default:
                if (FileToolsBackUp::quit_flag) {
                    PRINT_VERBOSE(1, "Operation Aborted.\n");
                } else if (cmd == CMD_LEAVE) {
                    PRINT_VERBOSE(1, "Operation Failed.\n");
                } else {
                    PRINT_VERBOSE(1, "Operation Successful.\n");
                }
                break;
            }
        }
        if (lockfile) {
            afc_file_lock(afc, lockfile, AFC_LOCK_UN);
            afc_file_close(afc, lockfile);
            lockfile = 0;
            if (cmd == CMD_BACKUP || cmd == CMD_RESTORE)
                FileToolsBackUp::do_post_notification(device, NP_SYNC_DID_FINISH);
        }
    }else {
        printf("ERROR: Could not start service %s: %s\n", MOBILEBACKUP2_SERVICE_NAME, lockdownd_strerror(ldret));
        lockdownd_client_free(lockdown);
        lockdown = NULL;
    }

    freeBackUpVar();
}

void IdeviceBackUp::start()
{
    if(th == nullptr){
        FileToolsBackUp::quit_flag = 0;
        th = new std::thread(&IdeviceBackUp::BackUp,this);
    }
}

void IdeviceBackUp::stop()
{
    if(th){
        FileToolsBackUp::quit_flag = 1;
        th->join();
    }
}
