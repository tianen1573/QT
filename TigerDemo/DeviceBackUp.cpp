#include "DeviceBackUp.h"

#define TOOL_NAME "DeviceBackup"
#define LOCK_ATTEMPTS 50
#define LOCK_WAIT 200000

DeviceBackUp::DeviceBackUp(QObject *parent)
    : QObject{parent}
{

}

void DeviceBackUp::backUp()
{

}

bool DeviceBackUp::init()
{
    m_willEncrypt = false;
    m_totalProgress = 0.0;
    m_blockProgress = 0.0;
    m_backupErrCode = 0;
    m_lockfile = 0;

    if(m_quitFlag || !connectDevice())
        return false;
    if(m_quitFlag || !connectLockdownd())
        return false;
    if(m_quitFlag || !connectNp())
        return false;
    if(m_quitFlag || !connectMobilBp2())
        return false;
    if(m_quitFlag || !exchangeVersion())
        return false;
    if(m_quitFlag || !connectAFC())
        return false;
    if(m_quitFlag || !lockAFCFile())
        return false;


    return true;
}

bool DeviceBackUp::connectDevice()
{
    emit logShow("连接设备...\n");

    if(IDEVICE_E_SUCCESS == m_device.createIdevice()){
        m_udid = m_device.getUdid();
        m_device.freeIdevice();
    }else {
        emit logShow("设备连接失败...\n");
        return false;
    }

    auto ret = m_device.createIdeviceWithOptions(m_udid, IDEVICE_LOOKUP_USBMUX);
    if(IDEVICE_E_SUCCESS != ret){
        emit logShow("设备连接失败...\n");
        return false;
    }

    return true;
}

bool DeviceBackUp::connectLockdownd()
{
    emit logShow("连接lockdownd服务...\n");
    auto ret = m_lockdown.createLockdowndWithHandshake(m_device);
    if(LOCKDOWN_E_SUCCESS != ret) {
        emit logShow("lockdownd服务连接失败...\n");
        return false;
    }
    return true;
}

bool DeviceBackUp::connectNp()
{
    emit logShow("连接NP服务...\n");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startService(NP_SERVICE_NAME,&service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        m_notificationProxy.createNp(m_device,service);
        m_notificationProxy.observeNotifications();
        lockdownd_service_descriptor_free(service);
        return true;
    } else{
        emit logShow("NP服务连接失败");
        return false;
    }
}

bool DeviceBackUp::connectAFC()
{
    emit logShow("连接AFC服务...\n");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startService(AFC_SERVICE_NAME, &service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service->port) {
        m_afc.createAFC(m_device,service);
        lockdownd_service_descriptor_free(service);
        return true;
    } else {
        emit logShow("AFC服务连接失败...\n");
        return false;
    }
}

bool DeviceBackUp::lockAFCFile()
{
    // 通知
    // 打开文件
    // 加锁独占

    emit logShow("锁定afc文件...\n");
    afc_error_t aerr;
    bool success = true;
    m_notificationProxy.postNotifications(NP_SYNC_WILL_START);// 通知
    m_afc.openFile("/com.apple.itunes.lock_sync", AFC_FOPEN_RW, &m_lockfile); // 打开
    if (m_lockfile) {
        m_notificationProxy.postNotifications(NP_SYNC_LOCK_REQUEST);
        for (int i = 0; i < LOCK_ATTEMPTS && !m_quitFlag; i++) {
            aerr = m_afc.lockFile(m_lockfile, AFC_LOCK_EX);
            if (aerr == AFC_E_SUCCESS) {
                m_notificationProxy.postNotifications(NP_SYNC_DID_START);
                success = true;
                break;
            } else if (aerr == AFC_E_OP_WOULD_BLOCK) {
                std::this_thread::sleep_for(std::chrono::microseconds(LOCK_WAIT)); // 暂停等待
                continue;
            } else {
                break;
            }
        }
        if (!success) {
            m_afc.closeFile(m_lockfile);
            m_lockfile = 0;
            emit logShow("afc文件锁定失败...\n");
            return false;
        }
    }
    return true;
}

bool DeviceBackUp::connectMobilBp2()
{
    emit logShow("连接备份服务...\n");
    lockdownd_service_descriptor_t service = nullptr;
    lockdownd_error_t ldret = m_lockdown.startServiceWithEscrowBag(MOBILEBACKUP2_SERVICE_NAME, &service);
    if ((ldret == LOCKDOWN_E_SUCCESS) && service && service->port) {
        QString tmp;
        tmp.sprintf("\"%s\" service on port %d.\n", MOBILEBACKUP2_SERVICE_NAME, service->port);
        emit logShow(tmp);
        m_mobilebackup2.createMbp2(m_device,service);
        lockdownd_service_descriptor_free(service);
        return true;
    } else  {
        emit logShow("备份服务连接失败...\n");
        return false;
    }
}

bool DeviceBackUp::exchangeVersion()
{
    emit logShow("交换版本信息...\n");
    double local_versions[2] = {2.0, 2.1};
    double remote_version = 0.0;
    mobilebackup2_error_t err = m_mobilebackup2.versionExchange(local_versions, 2, &remote_version);
    if (MOBILEBACKUP2_E_SUCCESS != err) {
        emit emit logShow("版本信息交换失败...\n");
        return false;
    }
    return true;
}
