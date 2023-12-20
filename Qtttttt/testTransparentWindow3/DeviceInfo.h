#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QVariant>
#include "CommonGlobal.h"
#include "Common.h"

class TIGERDR_COMMON_LIBRARY_EXPORT DeviceInfo
{
public:
    DeviceInfo();

    ///
    /// \brief 获取当前系统版本
    /// \return
    ///
    IOSVERSION currentIOSVersion();
public:
    // getter and setter
    const QString &udid() const;
    void setUdid(const QString &newUdid);
    const QString &deviceName() const;
    void setDeviceName(const QString &newDeviceName);
    const QString &deviceType() const;
    void setDeviceType(const QString &newDeviceType);
    const QString &deviceTypeName() const;
    void setDeviceTypeName(const QString &newDeviceTypeName);
    const QString &deviceVersion() const;
    void setDeviceVersion(const QString &newDeviceVersion);
    uint64_t deviceDiskCapacity() const;
    void setDeviceDiskCapacity(uint64_t newDeviceDiskCapacity);
    uint64_t deviceDiskUsed() const;
    void setDeviceDiskUsed(uint64_t newDeviceDiskUsed);
    uint64_t deviceDiskAvailable() const;
    void setDeviceDiskAvailable(uint64_t newDeviceDiskAvailable);
    bool isEncrytion() const;
    void setIsEncrytion(bool newIsEncrytion);
    const QString &backupPassword() const;
    void setBackupPassword(const QString &newBackupPassword);
    const QList<QString> &listBundleID() const;
    void setListBundleID(const QList<QString> &newListBundleID);
    double timestamp() const;
    void setTimestamp(double newTimestamp);
    float Size() const;
    void setSize(float newSize);
    const QString &absolutePath() const;
    void setAbsolutePath(const QString &newAbsolutePath);

    const QString &backupType() const;
    void setBackupType(const QString &newBackupType);

    QString buildVerion() const;
    void setBuildVerion(const QString &newBuildVerion);

    QString productVersion() const;
    void setProductVersion(const QString &newProductVersion);

    QString productType() const;
    void setProductType(const QString &newProductType);

    QString serialNumber() const;
    void setSerialNumber(const QString &newSerialNumber);

private:
    // 设备udid
    QString m_udid;
    // 设备名称
    QString m_deviceName;
    // 设备型号: (14, 9)
    QString m_deviceType;
    QString m_deviceTypeName;
    // 设备系统版本
    QString m_deviceVersion;
    // 设备总容量
    uint64_t m_deviceDiskCapacity;
    // 设备已使用容量
    uint64_t m_deviceDiskUsed;
    // 设备可使用容量
    uint64_t m_deviceDiskAvailable;
    // 备份时间戳
    uint64_t m_timestamp;
    // 该备份是否加密
    bool m_isEncrytion;
    //加密备份的密码
    QString m_backupPassword;
    QList<QString> m_listBundleID;
    // 该备份文件大小
    float m_size;
    // 该备份文件所在目录的绝对路径
    QString m_absolutePath;
    QString m_backupType;
    // 设备构建版本
    QString m_buildVerion;
    // 设备产品版本
    QString m_productVersion;
    // 设备产品类型
    QString m_productType;
    // 设备序列号
    QString m_serialNumber;
};

typedef QSharedPointer<DeviceInfo> DeviceInfoPtr;

Q_DECLARE_METATYPE(DeviceInfoPtr)
Q_DECLARE_METATYPE(DeviceInfo*)
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
