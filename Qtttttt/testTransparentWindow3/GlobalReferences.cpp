#include "GlobalReferences.h"

//#include <QDebug>
//#include <utils/OSUtils.h>
//#include <utils/WindowsAPIUtil.h>
//#include <QCoreApplication>
//#include <QCryptographicHash>
//#include <QStandardPaths>
//#include "../tigerdr/accountapplication/AccountManager.h"

//GlobalReferences * GlobalReferences::m_references = nullptr;

//GlobalReferences *GlobalReferences::instance()
//{
//    if(m_references == nullptr) {
//        m_references = new GlobalReferences;
//    }
//    return m_references;
//}

//DeviceInfoPtr GlobalReferences::getDevice()
//{
//    return this->device;
//}

//void GlobalReferences::setDevice(DeviceInfoPtr& device)
//{
//    this->device = device;
//}

//GlobalReferences::GlobalReferences():
//    config(OSUtils::pathJoin({QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), "Tiger" ,"config.ini"}), QSettings::IniFormat)
//{
//    qDebug() << OSUtils::pathJoin({QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), "Tiger" ,"config.ini"});
//    // 获取软件版本
//    this->version = QString("%1.%2.%3.%4").arg(MAIN_VERSION).arg(MINOR_VERSION).arg(RELEASE_VERSION).arg(BUILD_NUMBER);
//    // 加载配置文件
//    loadSetting();
//    // 创建账号管理器
//    this->m_acountManager = AccountManager::instance();
//    qDebug() << "GlobalReferences load...\r\n";
//}

//void GlobalReferences::setLicense(LicensePtr newLicense)
//{
//    m_license = newLicense;
//}

//QWidget *GlobalReferences::mainWindow() const
//{
//    return m_mainWindow;
//}

//void GlobalReferences::setMainWindow(QWidget *newMainWindow)
//{
//    m_mainWindow = newMainWindow;
//}

//QStringList GlobalReferences::customBackupPath()
//{
//    return m_customBackupPath;
//}

//void GlobalReferences::setCustomBackupPath(const QStringList &newCustomBackupPath)
//{
//    m_customBackupPath = newCustomBackupPath;
//}

//BACKUPMODE GlobalReferences::mode() const
//{
//    return m_mode;
//}

//void GlobalReferences::setMode(BACKUPMODE newMode)
//{
//    m_mode = newMode;
//}


//bool GlobalReferences::isReduceDiskUsage() const
//{
//    return m_isReduceDiskUsage;
//}

//void GlobalReferences::setIsReduceDiskUsage(bool newIsReduceDiskUsage)
//{
//    m_isReduceDiskUsage = newIsReduceDiskUsage;
//}

//QString GlobalReferences::appName() const
//{
//    return m_appName;
//}

//QString GlobalReferences::anlyticEventType() const
//{
//    static QString appName = QString("User action [%1]").arg(m_appName);
//    return appName;
//}

//void GlobalReferences::setAppName(const QString &newAppName)
//{
//    m_appName = newAppName;
//}

//AccountManager *GlobalReferences::acountManager()
//{
//    return m_acountManager;
//}

//QString GlobalReferences::tempPath() const
//{
//    return m_tempPath;
//}

//void GlobalReferences::setTempPath(const QString &newTempPath)
//{
//    m_tempPath = newTempPath;
//}

//QString GlobalReferences::defaultBackupPath() const
//{
//    return m_defaultBackupPath;
//}

//void GlobalReferences::setDefaultBackupPath(const QString &newDefaultBackupPath)
//{
//    m_defaultBackupPath = newDefaultBackupPath;
//}

//LicensePtr GlobalReferences::license() const
//{
//    return m_license;
//}

//// 更新license信息
//void GlobalReferences::updateLincense()
//{
//    this->m_license = this->m_acountManager->getLicenceByProductSerial(this->m_productId);
//    this->isActivate = this->m_license.isNull() ? false : true;
//}

//QString GlobalReferences::getVersion() const
//{
//    return version;
//}

//void GlobalReferences::setVersion(const QString &newVersion)
//{
//    version = newVersion;
//}

//bool GlobalReferences::getIsFirstRun() const
//{
//    return isFirstRun;
//}

//void GlobalReferences::setIsFirstRun(bool newIsFirstRun)
//{
//    isFirstRun = newIsFirstRun;
//    config.setValue("Backup/IsFirstRun", isFirstRun);
//}

//QLocale::Language GlobalReferences::getLanguage()
//{
//    if (config.contains("Language")) {
//        return (QLocale::Language)config.value("Language").toInt();
//    } else {
//        QLocale loc = QLocale::system();
//        QLocale::Language defaultLanguage = loc.language();
//        // 除简体中文外，默认英文
//        if (loc.language() != QLocale::Language::Chinese) {
//            defaultLanguage = QLocale::Language::English;
//        }
//        this->setLanguage(defaultLanguage);
//        return defaultLanguage;
//    }
//}

//void GlobalReferences::setLanguage(const QLocale::Language &newLanguage)
//{
//    language = newLanguage;
//    config.setValue("Language", language);
//}

//QString GlobalReferences::getLanguageStr()
//{
//    QString result;
//    if(this->language == QLocale::Language::Chinese) {
//        result = "zh_CN";
//    } else {
//        result = "en_US";
//    }
//    return result;
//}

//void GlobalReferences::loadSetting()
//{
//    // 默认备份路径
//    if(config.contains("Backup/BackupPath")) {
//        QString path = QString::fromUtf8(QByteArray::fromBase64(config.value("Backup/BackupPath").toByteArray()));
//        this->m_defaultBackupPath = QDir::toNativeSeparators(path);
//    } else {
//#ifdef Q_OS_WIN
//        QString driver = WindowsAPIUtil::getMaxDriver();
//        this->m_defaultBackupPath = QDir::toNativeSeparators(QDir::toNativeSeparators(OSUtils::pathJoin({driver,"tigerdrios"})));
//#else //Q_OS_MAC
//        this->m_defaultBackupPath = QDir::toNativeSeparators(OSUtils::pathJoin({QDir::homePath(),"tigerdrios"}));
//#endif
//    }

//    // 默认缓存路径
//    if(config.contains("Backup/TempPath")) {
//        QString tempPath = QString::fromUtf8(QByteArray::fromBase64(config.value("Backup/TempPath").toByteArray()));
//        this->m_tempPath = QDir::toNativeSeparators(tempPath);
//    } else {
//#ifdef Q_OS_WIN
//        QString driver = WindowsAPIUtil::getMaxDriver();
//        this->m_tempPath = QDir::toNativeSeparators(QDir::toNativeSeparators(OSUtils::pathJoin({driver,"tigerdrios", "temp"})));
//#else //Q_OS_MAC
//    this->m_tempPath = QDir::toNativeSeparators(OSUtils::pathJoin({QDir::homePath(),"tigerdrios", "temp"}));
//#endif
//    }

//    // 用户自定义备份路径
//    if(config.contains("Backup/CustomBackupPath")) {
//        QString customPath = QString::fromUtf8(QByteArray::fromBase64(config.value("Backup/CustomBackupPath").toByteArray()));
//        this->m_customBackupPath = customPath.split(",");
//        foreach(auto path, this->m_customBackupPath) {
//            if(path.isEmpty()) {
//                this->m_customBackupPath.removeOne(path);
//            }
//        }
//    }

//    // 是否开启减少磁盘空间
//    if(config.contains("Backup/ReduceDiskUsage")) {
//        this->m_isReduceDiskUsage = config.value("Backup/ReduceDiskUsage").toBool();
//    } else {
//        this->m_isReduceDiskUsage = true;
//    }

//    // 软件语言
//    if (config.contains("Language")) {
//        language = (QLocale::Language)config.value("Language").toInt();
//    }

//    // 是否第一次运行
//    if (config.contains("Backup/IsFirstRun")) {
//        isFirstRun = config.value("Backup/IsFirstRun").toBool();
//    }
//}

//void GlobalReferences::loadLicense(const QString& productId)
//{
//    this->m_productId = productId;
//    this->m_license = this->m_acountManager->getLicenceByProductSerial(productId);
//    this->isActivate = this->m_license.isNull() ? false : true;
//}

//// 保存配置文件
//void GlobalReferences::saveSetting()
//{
//    config.setValue("Backup/BackupPath", this->m_defaultBackupPath.toUtf8().toBase64());
//    config.setValue("Backup/TempPath", this->m_tempPath.toUtf8().toBase64());
//    config.setValue("Backup/ReduceDiskUsage", this->m_isReduceDiskUsage);
//    QString customBackupPath;
//    foreach(auto path, this->m_customBackupPath) {
//        if(!path.isEmpty()) {
//            customBackupPath.append(path).append(",");
//        }
//    }
//    config.setValue("Backup/CustomBackupPath", customBackupPath.toUtf8().toBase64());
//    config.sync();
//}

//bool GlobalReferences::getIsActivate() const
//{
//    return isActivate;
//}

//void GlobalReferences::setIsActivate(bool newIsActivate)
//{
//    isActivate = newIsActivate;
//}

//GlobalReferences *GlobalReferences::references() const
//{
//    return m_references;
//}

//void GlobalReferences::setReferences(GlobalReferences *newReferences)
//{
//    m_references = newReferences;
//}
