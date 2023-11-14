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
#include <libimobiledevice-glue/utils.h>

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

    void start(); // 在一个线程上开启备份
    void stop(); // 结束备份
    bool init();
    void clear();
    void backupThreadCallBack();
signals:

    void logShow(const QString& str);

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

    bool m_isRetain = true;
};

#endif // DEVICEBACKUP_H
