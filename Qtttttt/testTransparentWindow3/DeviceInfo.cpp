#include "DeviceInfo.h"

DeviceInfo::DeviceInfo()
{
    this->m_deviceDiskCapacity = 0;
    this->m_deviceDiskUsed = 0;
    this->m_deviceDiskAvailable = 0;
    this->m_timestamp = 0;
    this->m_isEncrytion = false;
    this->m_size = 0;
}

// 获取当前系统版本
IOSVERSION DeviceInfo::currentIOSVersion()
{
    IOSVERSION result = IOS_VERSION_UNKNOW;
    result = (IOSVERSION)this->m_deviceVersion.split('.')[0].toInt();
    return result;
}

const QString &DeviceInfo::udid() const
{
    return m_udid;
}

void DeviceInfo::setUdid(const QString &newUdid)
{
    m_udid = newUdid;
}

const QString &DeviceInfo::deviceName() const
{
    return m_deviceName;
}

void DeviceInfo::setDeviceName(const QString &newDeviceName)
{
    m_deviceName = newDeviceName;
}

const QString &DeviceInfo::deviceType() const
{
    return m_deviceType;
}

void DeviceInfo::setDeviceType(const QString &newDeviceType)
{
    m_deviceType = newDeviceType;
}

const QString &DeviceInfo::deviceTypeName() const
{
    return m_deviceTypeName;
}

void DeviceInfo::setDeviceTypeName(const QString &newDeviceTypeName)
{
    m_deviceTypeName = newDeviceTypeName;
}

const QString &DeviceInfo::deviceVersion() const
{
    return m_deviceVersion;
}

void DeviceInfo::setDeviceVersion(const QString &newDeviceVersion)
{
    m_deviceVersion = newDeviceVersion;
}

uint64_t DeviceInfo::deviceDiskCapacity() const
{
    return m_deviceDiskCapacity;
}

void DeviceInfo::setDeviceDiskCapacity(uint64_t newDeviceDiskCapacity)
{
    m_deviceDiskCapacity = newDeviceDiskCapacity;
}

uint64_t DeviceInfo::deviceDiskUsed() const
{
    return m_deviceDiskUsed;
}

void DeviceInfo::setDeviceDiskUsed(uint64_t newDeviceDiskUsed)
{
    m_deviceDiskUsed = newDeviceDiskUsed;
}

uint64_t DeviceInfo::deviceDiskAvailable() const
{
    return m_deviceDiskAvailable;
}

void DeviceInfo::setDeviceDiskAvailable(uint64_t newDeviceDiskAvailable)
{
    m_deviceDiskAvailable = newDeviceDiskAvailable;
}

bool DeviceInfo::isEncrytion() const
{
    return m_isEncrytion;
}

void DeviceInfo::setIsEncrytion(bool newIsEncrytion)
{
    m_isEncrytion = newIsEncrytion;
}

const QString &DeviceInfo::backupPassword() const
{
    return m_backupPassword;
}

void DeviceInfo::setBackupPassword(const QString &newBackupPassword)
{
    m_backupPassword = newBackupPassword;
}

const QList<QString> &DeviceInfo::listBundleID() const
{
    return m_listBundleID;
}

void DeviceInfo::setListBundleID(const QList<QString> &newListBundleID)
{
    m_listBundleID = newListBundleID;
}

double DeviceInfo::timestamp() const
{
    return m_timestamp;
}

void DeviceInfo::setTimestamp(double newTimestamp)
{
    m_timestamp = newTimestamp;
}

float DeviceInfo::Size() const
{
    return m_size;
}

void DeviceInfo::setSize(float newSize)
{
    m_size = newSize;
}

const QString &DeviceInfo::absolutePath() const
{
    return m_absolutePath;
}

void DeviceInfo::setAbsolutePath(const QString &newAbsolutePath)
{
    m_absolutePath = newAbsolutePath;
}

const QString &DeviceInfo::backupType() const
{
    return m_backupType;
}

void DeviceInfo::setBackupType(const QString &newBackupType)
{
    m_backupType = newBackupType;
}

QString DeviceInfo::buildVerion() const
{
    return m_buildVerion;
}

void DeviceInfo::setBuildVerion(const QString &newBuildVerion)
{
    m_buildVerion = newBuildVerion;
}

QString DeviceInfo::productVersion() const
{
    return m_productVersion;
}

void DeviceInfo::setProductVersion(const QString &newProductVersion)
{
    m_productVersion = newProductVersion;
}

QString DeviceInfo::productType() const
{
    return m_productType;
}

void DeviceInfo::setProductType(const QString &newProductType)
{
    m_productType = newProductType;
}

QString DeviceInfo::serialNumber() const
{
    return m_serialNumber;
}

void DeviceInfo::setSerialNumber(const QString &newSerialNumber)
{
    m_serialNumber = newSerialNumber;
}
