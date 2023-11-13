#ifndef IDEVICEID_H
#define IDEVICEID_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>


#define TOOL_NAME "idevice_id"

class IdeviceId : public QWidget
{
    Q_OBJECT
public:
    explicit IdeviceId(QWidget *parent = nullptr);

signals:
    void updateTxt(const QString& txt);

private slots:
    void SelectId();
    void SelectName();



private:
    idevice_t device = NULL; // 设备对象
    lockdownd_client_t client = NULL; // lockdownd服务客客户端
    char *device_name = NULL; // 手机设备名字
    idevice_info_t *dev_list = NULL;
    int i = 0;
    char *udid = NULL;

    int ret = 0;
    QString strerr;
};

#endif // IDEVICEID_H
