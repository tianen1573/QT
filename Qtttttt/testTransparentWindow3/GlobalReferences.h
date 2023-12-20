#ifndef GLOBALREFERENCES_H
#define GLOBALREFERENCES_H

#include <QString>
#include <QSettings>
#include <QLocale>
#include <QWidget>
#include <DeviceInfo.h>
#include "Common.h"
#include "License.h"
#include "CommonGlobal.h"

//class AccountManager;

/////
///// \brief 全局数据信息
/////
//class TIGERDR_COMMON_LIBRARY_EXPORT GlobalReferences
//{
//public:
//    static GlobalReferences* instance();

//    DeviceInfoPtr getDevice();

//    void setDevice(DeviceInfoPtr& device);

//    GlobalReferences *references() const;
//    void setReferences(GlobalReferences *newReferences);

//    bool getIsActivate() const;
//    void setIsActivate(bool newIsActivate);

//    QLocale::Language getLanguage();
//    void setLanguage(const QLocale::Language &newLanguage);

//    QString getLanguageStr();

//    ///
//    /// \brief 加载配置文件
//    ///
//    void loadSetting();

//    ///
//    /// \brief 加载license
//    ///
//    void loadLicense(const QString& productId);

//    ///
//    /// \brief 加载网站配置文件
//    ///
//    void loadWebSetting();

//    ///
//    /// \brief 保存配置文件
//    ///
//    void saveSetting();
//    bool getIsFirstRun() const;
//    void setIsFirstRun(bool newIsFirstRun);
//    QString getVersion() const;
//    void setVersion(const QString &newVersion);

//    LicensePtr license() const;
//    void setLicense(LicensePtr newLicense);

//    ///
//    /// \brief 更新license信息
//    ///
//    void updateLincense();

//    QString defaultBackupPath() const;
//    void setDefaultBackupPath(const QString &newDefaultBackupPath);

//    QString tempPath() const;
//    void setTempPath(const QString &newTempPath);

//    AccountManager *acountManager();

//    QString appName() const;
//    void setAppName(const QString &newAppName);

//    bool isReduceDiskUsage() const;
//    void setIsReduceDiskUsage(bool newIsReduceDiskUsage);

//    BACKUPMODE mode() const;
//    void setMode(BACKUPMODE newMode);

//    QStringList customBackupPath();
//    void setCustomBackupPath(const QStringList &newCustomBackupPath);

//    QString anlyticEventType() const;
//    QWidget *mainWindow() const;
//    void setMainWindow(QWidget *newMainWindow);

//private:
//    GlobalReferences();
//    static GlobalReferences* m_references;
//    AccountManager* m_acountManager;
//    // 当前App名称
//    QString m_appName;
//    // 当前系统语言
//    QLocale::Language language;
//    // 设备信息
//    DeviceInfoPtr device;
//    // 是否激活
//    bool isActivate;
//    // 软件版本
//    QString version;
//    // 配置文件
//    QSettings config;
//    // 是否是第一次运行
//    bool isFirstRun;
//    // 当前模式
//    BACKUPMODE m_mode;
//    // 是否减少空间占用,默认开
//    bool m_isReduceDiskUsage;
//    // 产品license
//    LicensePtr m_license;
//    // 默认备份路径
//    QString m_defaultBackupPath;
//    // 默认缓存路径
//    QString m_tempPath;
//    QString m_productId;
//    // 用户自定义备份路径
//    QStringList m_customBackupPath;
//    // 主页面
//    QWidget* m_mainWindow;
//};

#endif // GLOBALREFERENCES_H
