#ifndef LOCKDOWND_H
#define LOCKDOWND_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "libimobiledevice/libimobiledevice.h"
#include "libimobiledevice/lockdown.h"
#include "Device.h"

/*
 * 连接lockdownd服务
 * 获取对象：最基本的对象、完成交互的对象
 * 释放对象
 * 获取/设置：可以通过lockdownd客户端对象获取/设置设备的属性(设备的各种属性和配置，例如电池状态、声音设置、网络配置等)
 * 开启服务：正常的、带保管带的
*/
class Lockdownd : public QObject
{
    Q_OBJECT
public:
    explicit Lockdownd(QObject *parent = nullptr);
    virtual ~Lockdownd();
    lockdownd_client_t getLockdownd();

    lockdownd_error_t createLockdownd(const Device& device);
    lockdownd_error_t createLockdowndWithHandshake(const Device& device);
    lockdownd_error_t freeLockdownd();
    lockdownd_error_t pair();
    lockdownd_error_t getValue(const char* domain, const char* key, plist_t* nodeValue);
    lockdownd_error_t setValue(const char* domain, const char* key, plist_t nodeValue);
    lockdownd_error_t startService(const char* identifier, lockdownd_service_descriptor_t *service);
    lockdownd_error_t startServiceWithEscrowBag(const char* identifier, lockdownd_service_descriptor_t *service);

private:
    lockdownd_client_t m_lockdowndClient;
};

#endif // LOCKDOWND_H
