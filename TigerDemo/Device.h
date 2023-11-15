#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "libimobiledevice/libimobiledevice.h"

/*
 * 连接设备
 * 获取设备对象：最基本的对象、带参数的对象
 * 释放设备对象
 * 获取设备udid
*/
class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    virtual ~Device();
    idevice_t getIdevice() const;

    idevice_error_t openIdevice(const QString& udid = "");
    idevice_error_t openIdeviceWithOptions(const QString& udid, idevice_options options);
    idevice_error_t closeIdevice();
    QString getUdid();

private:

    idevice_t m_idevice;

};

#endif // DEVICE_H
