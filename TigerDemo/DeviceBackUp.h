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

class DeviceBackUp : public QObject
{
    Q_OBJECT
public:
    explicit DeviceBackUp(QObject *parent = nullptr);

    void backUp();
    bool init();

signals:

    void logShow(const QString& str);

private:
    bool connectDevice();
    bool connectLockdownd();
    bool connectNp();
    bool connectAFC();
    bool lockAFCFile();
    bool connectMobilBp2();
    bool exchangeVersion();
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
