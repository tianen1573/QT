#include "ideviceid.h"
#include <QDebug>
IdeviceId::IdeviceId(QWidget *parent)
    : QWidget{parent}
{

}
void IdeviceId::SelectId()
{
    strerr.resize(0);
    ret = idevice_get_device_list_extended(&dev_list, &i);
    if (ret == IDEVICE_E_UNKNOWN_ERROR) {
        strerr = "ERROR: Unable to retrieve device list!(-2)\n";
        ret = -2;
        emit updateTxt(strerr);
    }
    else if(i)
    {
        for (i = 0; dev_list[i] != NULL; i++) {
            strerr += QString(dev_list[i]->udid) + "(USB)\n";
        }
        emit updateTxt(strerr);
    }
    else
    {
        strerr = "ERROR: Could not get device!(-1)\n";
        ret = -1;
        emit updateTxt(strerr);
    }

    idevice_device_list_extended_free(dev_list);
    dev_list = NULL;

    QMessageBox::information(this, "DeviceID", strerr);
}
void IdeviceId::SelectName()
{
    strerr.clear();
    ret = idevice_new_with_options(&device, udid, IDEVICE_LOOKUP_USBMUX);
    if (!device) {
        strerr = "ERROR: No device.(-1)\n";
//        ui->textEdit->append(strerr);
        ret = -1;
        goto leave;
    }

    if (LOCKDOWN_E_SUCCESS != lockdownd_client_new(device, &client, TOOL_NAME)) {
        idevice_free(device);
        strerr = "ERROR: Connecting to device failed!(-2)\n";
//        ui->textEdit->append(strerr);
        ret = -2;
        goto leave;
    }

    if ((LOCKDOWN_E_SUCCESS != lockdownd_get_device_name(client, &device_name)) || !device_name) {
        strerr = "ERROR: Could not get device name!(-3)\n";
//        ui->textEdit->append(strerr);
        ret = -3;
        goto leave;
    }

leave:
    lockdownd_client_free(client);
    idevice_free(device);
    free(udid);
    client = NULL;
    device = NULL;
    udid = NULL;

    if (ret == 0) {
        strerr = device_name;
//        ui->textEdit->append(strerr + '\n');
    }
    if (device_name) {
        free(device_name);
        device_name = NULL;
    }


    QMessageBox::information(this, "DeviceName", strerr);
}
