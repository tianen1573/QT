#ifndef DEVICEBACKUP_H
#define DEVICEBACKUP_H

#include <QObject>
#include <thread>
#include <QObject>
#include <QString>
#include <QFile>
#include <QSharedPointer>

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
    bool initService();
    void initVar();
    void clear();
    void backupThreadCallBack();
private slots:
    void start(); // 在一个线程上开启备份
    void stop(); // 结束备份
signals:
    void logShow(const QString& str);
    void displayWarningDialog(const QString& name, const QString& desc);
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
    // 服务或文件对象
    Device m_device;
    Lockdownd m_lockdown;
    NP m_notificationProxy;
    AFC m_afc;
    uint64_t m_lockfile = 0;
    MobileBackUp2 m_mobilebackup2;

    // 备份需要的变量
    QString  m_udid; // udid
    bool m_forceFullBackup; // 是否全量备份
    bool m_willEncrypt; // 是否加密
    QString m_backupPath = "D:/TestBackUp"; // 备份路径
    char * backup_dir = "D:/TestBackUp"; // C指针形式
    bool m_quitFlag = false; // 非正常退出标志(外部，内部)
    bool m_progress_finished = false; // 正常退出
    double m_overall_progress = 0.0f; // 整体进度

    std::thread * m_thread = nullptr;

    // 备份过程中需要的变量
    QString m_oldPwd = "";
    QString m_newPwd = "";
    plist_t node_tmp = NULL;
    int m_backupErrCode = 0;
    int errcode;
    char * errdesc;
    struct stat st;
    int result_code = -1;
    mobilebackup2_error_t err;
    uint64_t file_count = 0;

};

#endif // DEVICEBACKUP_H
