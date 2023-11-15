#include "Device.h"



Device::Device(QObject *parent)
    : QObject{parent}, m_idevice(nullptr)
{

}

Device::~Device()
{
    if(m_idevice != nullptr)
        closeIdevice();
}

idevice_t Device::getIdevice() const
{
    return m_idevice;
}

idevice_error_t Device::openIdevice(const QString &udid)
{
    if(m_idevice)
        closeIdevice();
    idevice_error_t errRet = IDEVICE_E_SUCCESS;
    if(udid.isEmpty())
        errRet = idevice_new(&m_idevice, NULL);
    else
        errRet = idevice_new(&m_idevice, udid.toLocal8Bit());

    return errRet;
}

idevice_error_t Device::openIdeviceWithOptions(const QString &udid, idevice_options options)
{
    /*
     * IDEVICE_LOOKUP_NETWORK：通过网络查找可用的设备。
     * IDEVICE_LOOKUP_USBMUX：通过 USBMux 查找可用的设备。
     * IDEVICE_LOOKUP_USBMUX_RECONNECT：如果设备断开连接，自动尝试重新连接。
     * IDEVICE_LOOKUP_NETWORK_RECONNECT：如果设备断开连接，自动尝试重新连接。
    */
    return idevice_new_with_options(&m_idevice, udid.toLocal8Bit(), options);
}

idevice_error_t Device::closeIdevice()
{

    auto errRet = idevice_free(m_idevice);
    m_idevice = nullptr;

    return errRet;
}

QString Device::getUdid()
{
    QString udid;
    char * buff = nullptr;
    if(IDEVICE_E_SUCCESS == idevice_get_udid(m_idevice, &buff) && nullptr != buff)
    {
        udid = QString::fromUtf8(buff);
        free(buff);
    }

    return udid;
}
