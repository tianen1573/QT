#include "MobileBackUp2.h"

MobileBackUp2::MobileBackUp2(QObject *parent)
    : QObject{parent}, m_mbp2(nullptr)
{

}

MobileBackUp2::~MobileBackUp2()
{

}

mobilebackup2_client_t MobileBackUp2::handle() const
{
    return m_mbp2;
}

mobilebackup2_error_t MobileBackUp2::createMbp2(const Device &device, const lockdownd_service_descriptor_t service)
{
    if(m_mbp2)
        freeMbp2();

    return mobilebackup2_client_new(device.getIdevice(), service,&m_mbp2);
}

mobilebackup2_error_t MobileBackUp2::freeMbp2()
{
    auto errRet = mobilebackup2_client_free(m_mbp2);
    m_mbp2 = nullptr;

    return errRet;
}

mobilebackup2_error_t MobileBackUp2::sendRaw(const char *data, uint32_t len, uint32_t *sent)
{
    return mobilebackup2_send_raw(m_mbp2, data, len, sent);
}

mobilebackup2_error_t MobileBackUp2::recvRaw(char *data, uint32_t len, uint32_t *rlen)
{
    return mobilebackup2_receive_raw(m_mbp2,data,len,rlen);
}

mobilebackup2_error_t MobileBackUp2::versionExchange(double local_versions[], char count, double *remote_version)
{
    return mobilebackup2_version_exchange(m_mbp2,local_versions,count,remote_version);
}

mobilebackup2_error_t MobileBackUp2::sendRequest(const char *request, const char *targetUdid, const char *sourceUdid, plist_t options)
{
    return mobilebackup2_send_request(m_mbp2,request,targetUdid,sourceUdid,options);
}

mobilebackup2_error_t MobileBackUp2::sendMessage(const char *message, plist_t options)
{
    return mobilebackup2_send_message(m_mbp2,message,options);
}

mobilebackup2_error_t MobileBackUp2::receiveMessage(plist_t *msg, char **dlmessage)
{
    return mobilebackup2_receive_message(m_mbp2,msg,dlmessage);
}

mobilebackup2_error_t MobileBackUp2::sendStatusResponse(int statusCode, const char *status1, plist_t status2)
{
    mobilebackup2_error_t err;
    if (!status2) {
        plist_t emptydict = plist_new_dict();
        err = mobilebackup2_send_status_response(m_mbp2, statusCode, status1, emptydict);
        plist_free(emptydict);
    } else {
        err = mobilebackup2_send_status_response(m_mbp2, statusCode, status1, status2);
    }
    return err;
}
