#include "NP.h"

NP::NP(QObject *parent)
    : QObject{parent}
{

}

NP::~NP()
{

}

np_client_t NP::getNpClient() const
{
    return m_npClient;
}

np_error_t NP::createNp(const Device &device, const lockdownd_service_descriptor_t service)
{
    if(m_npClient)
        freeNp();
    auto errRet = np_client_new(device.getIdevice(), service, &m_npClient);
    if(NP_E_SUCCESS == errRet){
        np_set_notify_callback(m_npClient, NP::npCallback, this);
    }

    return errRet;
}

np_error_t NP::freeNp()
{
    auto errRet = np_client_free(m_npClient);
    m_npClient = nullptr;

    return errRet;
}

np_error_t NP::observeNotifications()
{
    const char *noties[5] = {
        NP_SYNC_CANCEL_REQUEST,
        NP_SYNC_SUSPEND_REQUEST,
        NP_SYNC_RESUME_REQUEST,
        NP_BACKUP_DOMAIN_CHANGED,
        NULL
    };
    return np_observe_notifications(m_npClient, noties);
}

np_error_t NP::postNotifications(const char *notification)
{
    return np_post_notification(m_npClient, notification);
}

void NP::npCallback(const char *notification, void *user_data)
{
    // 打印日志
    // 判断是否终止并设置条件
}
