#include "Device.h"



Device::Device(QObject *parent)
    : QObject{parent}, m_idevice(nullptr)
{

}

Device::~Device()
{

}

idevice_t Device::getIdevice() const
{
    return m_idevice;
}

idevice_error_t Device::createIdevice(const QString &udid)
{
    if(m_idevice)
        freeIdevice();
    idevice_error_t errRet = IDEVICE_E_SUCCESS;
    if(udid.isEmpty())
        errRet = idevice_new(&m_idevice, NULL);
    else
        errRet = idevice_new(&m_idevice, udid.toLocal8Bit());

    return errRet;
}

idevice_error_t Device::createIdeviceWithOptions(const QString &udid, idevice_options options)
{
    return idevice_new_with_options(&m_idevice, udid.toLocal8Bit(), options);
}

idevice_error_t Device::freeIdevice()
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
        udid = QString::fromLocal8Bit(buff);
        free(buff);
    }

    return udid;
}
