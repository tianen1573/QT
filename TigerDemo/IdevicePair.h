#ifndef IDEVICEPAIR_H
#define IDEVICEPAIR_H

#include <QWidget>
#include <QMessageBox>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

#define TOOL_NAME "idevice_pair"

class IdevicePair : public QWidget
{
    Q_OBJECT
public:
    explicit IdevicePair( QWidget *parent = nullptr);

signals:

private slots:
    void DevicePair();
private:
    idevice_t device = NULL; // 设备对象
    lockdownd_client_t client = NULL;
    lockdownd_error_t lerr; // 错误码
    char *udid = NULL;

    int ret = 0;
    QString strerr;

};

#endif // IDEVICEPAIR_H
