#ifndef LOCKDOWND_H
#define LOCKDOWND_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "libimobiledevice/libimobiledevice.h"
#include "libimobiledevice/lockdown.h"
#include "Device.h"

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
