#include "idevicepair.h"

IdevicePair::IdevicePair(QWidget *parent)
    : QWidget{parent}
{

}

void IdevicePair::DevicePair()
{
    strerr.resize(0);
    ret = idevice_new_with_options(&device, udid, IDEVICE_LOOKUP_USBMUX);
    if (ret != IDEVICE_E_SUCCESS) {
        if (udid) {
            strerr = "No device found with udid[" + QString(udid) + "].(-1)\n";
        } else {
            strerr = "No device found.(-1)\n";
        }
        ret = -1;
//        ui->textEdit->append(strerr);
        goto leave;
    }
    if (!udid) {
        ret = idevice_get_udid(device, &udid);
        if (ret != IDEVICE_E_SUCCESS) {
            strerr = "ERROR: Could not get device udid, error code " + QString::number(ret) + ".(-5)\n";
            ret = -5;
//            ui->textEdit->append(strerr);
            goto leave;
        }
    }
    lerr = lockdownd_client_new(device, &client, TOOL_NAME);
    if (lerr != LOCKDOWN_E_SUCCESS) {
        strerr = "ERROR: Could not connect to lockdownd, error code" + QString::number(lerr) + ".(-2)\n";
//        ui->textEdit->append(strerr);
        goto leave;
    }

    lerr = lockdownd_pair(client, NULL);
    if (lerr == LOCKDOWN_E_SUCCESS) {
//        ui->textEdit->append(strerr);
        strerr = "SUCCESS: Paired with device udid[" + QString(udid) + "].\n";
//        ui->textEdit->append(strerr);
    }
    else
    {
        strerr = "ERROR: Pairing failed(" + QString::number(lerr) + ").(-6)\n";
        strerr += "\n\n\n-19: 请在手机端信任设备\n";
//        ui->textEdit->append(strerr);
    }

leave:
    lockdownd_client_free(client);
    idevice_free(device);
    free(udid);
    udid = NULL;
    client = NULL;
    device = NULL;

    emit displayWarningDialog("Pair", strerr);
//    QMessageBox::information(this, "Pairing", strerr);
}
