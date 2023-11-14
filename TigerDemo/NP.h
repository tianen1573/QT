#ifndef NP_H
#define NP_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/notification_proxy.h>
#include "Device.h"

class NP : public QObject
{
    Q_OBJECT
public:
    explicit NP(QObject *parent = nullptr);
    virtual ~NP();
    np_client_t getNpClient() const;

    np_error_t createNp(const Device& device, const lockdownd_service_descriptor_t service);
    np_error_t freeNp();
    np_error_t observeNotifications();
    np_error_t postNotifications(const char *notification);
private:
    static void npCallback(const char *notification, void *user_data);
private:
    np_client_t m_npClient;

};

#endif // NP_H
