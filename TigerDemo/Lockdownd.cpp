#include "Lockdownd.h"

Lockdownd::Lockdownd(QObject *parent)
    : QObject{parent}, m_lockdowndClient(nullptr)
{

}

Lockdownd::~Lockdownd()
{

}

lockdownd_client_t Lockdownd::getLockdownd()
{
    return m_lockdowndClient;
}

lockdownd_error_t Lockdownd::openLockdownd(const Device &device)
{
    if(m_lockdowndClient)
        closeLockdownd();

    return lockdownd_client_new(device.getIdevice(), &m_lockdowndClient, NULL);
}

lockdownd_error_t Lockdownd::openLockdowndWithHandshake(const Device &device)
{
    if(m_lockdowndClient)
        closeLockdownd();

    return lockdownd_client_new_with_handshake(device.getIdevice(), &m_lockdowndClient, NULL);
}

lockdownd_error_t Lockdownd::closeLockdownd()
{
    auto errRet = lockdownd_client_free(m_lockdowndClient);
    m_lockdowndClient = nullptr;

    return errRet;
}

lockdownd_error_t Lockdownd::pair()
{
    return lockdownd_pair(m_lockdowndClient, NULL);
}


lockdownd_error_t Lockdownd::getValue(const char *domain, const char *key, plist_t *nodeValue)
{
    return lockdownd_get_value(m_lockdowndClient, domain, key, nodeValue);
}

lockdownd_error_t Lockdownd::setValue(const char *domain, const char *key, plist_t nodeValue)
{
    return lockdownd_set_value(m_lockdowndClient, domain, key, nodeValue);
}

lockdownd_error_t Lockdownd::startService(const char *identifier, lockdownd_service_descriptor_t *service)
{
    return lockdownd_start_service(m_lockdowndClient, identifier, service);
}

lockdownd_error_t Lockdownd::startServiceWithEscrowBag(const char *identifier, lockdownd_service_descriptor_t *service)
{
    return lockdownd_start_service_with_escrow_bag(m_lockdowndClient, identifier, service);
}


