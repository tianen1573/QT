#ifndef DEVICEBACKUP_H
#define DEVICEBACKUP_H

#include <QObject>
#include <thread>
#include <QObject>
#include <QString>
#include <QFile>
#include <QSharedPointer>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/installation_proxy.h>
#include <libimobiledevice/sbservices.h>
#include <libimobiledevice/diagnostics_relay.h>

#include "Device.h"
#include "Lockdownd.h"
#include "NP.h"
#include "AFC.h"
#include "MobileBackup2.h"

/*
 * 开启备份操作需要的对象和服务的集成
 * 对消息的实际处理
 * 流程控制、打印进度、开启线程
 *
*/
class DeviceBackUp : public QObject
{
    Q_OBJECT
public:
    explicit DeviceBackUp(QObject *parent = nullptr);
    bool init();
    void clear();
    void backupThreadCallBack();
private slots:
    void start(); // 在一个线程上开启备份
    void stop(); // 结束备份
signals:
    void logShow(const QString& str);
    void backupInProgress();
    void backupCompleted();
    void setProgressBar(int p);
private:
    // 开启备份服务的流程
    bool connectDevice();
    bool connectLockdownd();
    bool connectNp();
    bool connectAFC();
    bool lockAFCFile();
    bool connectMobilBp2();
    bool exchangeVersion();
    bool sendBackupRequest(bool isFullBackup = true);
    // 消息处理
    void messageLoop();
    bool handleMessageOne(plist_t message, const char * dlmsg);
    bool downloadFiles(plist_t message);
    bool uploadFiles(plist_t message);
    bool getFreeDiskSpace(plist_t message);
    bool purgeDiskSpace(plist_t message);
    bool contentsOfDirectory(plist_t message);
    bool createDirectory(plist_t message);
    bool moveFilesAndItems(plist_t message);
    bool removeFilesAndItems(plist_t message);
    bool copyItem(plist_t message);
    bool disconnect(plist_t message);
    bool processMessage(plist_t message);
    void setAndPrintOverallProgress(plist_t message, const char * dlmsg);
private:
    Device m_device;
    Lockdownd m_lockdown;
    NP m_notificationProxy;
    AFC m_afc;
    uint64_t m_lockfile = 0;
    MobileBackUp2 m_mobilebackup2;

    QString  m_udid = nullptr;
    bool m_forceFullBackup = true;
    QString m_backupPath = "D:/TestBackUp";
    const char * backup_dir = "D:/TestBackUp";
    bool m_quitFlag = false;
    std::thread * m_thread = nullptr;

    bool m_willEncrypt = false;
    QString m_oldPwd = "";
    QString m_newPwd = "";
    double m_totalProgress = 0.0;
    double m_blockProgress = 0.0;
    int m_backupErrCode = 0;
    uint64_t m_blockTotalSize = 0;
    uint64_t m_blockRecvSize = 0;


    plist_t node_tmp = NULL;
    int errcode;
    char * errdesc;
    struct stat st;
    int result_code = -1;
    mobilebackup2_error_t err;
    uint64_t file_count = 0;
    double m_overall_progress = 0.0f;
    bool m_progress_finished = false;
};

#endif // DEVICEBACKUP_H
