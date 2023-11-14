#ifndef MOBILEBACKUP2_H
#define MOBILEBACKUP2_H

#include <QObject>

#include "libimobiledevice/mobilebackup2.h"
#include "Device.h"

/*
 * 连接备份服务
 * 创建对象、释放对象
 * 交互版本
 * 发送数据、接收数据
 * 发送消息、接收消息
 * 发送消息处理响应
*/
class MobileBackUp2 : public QObject
{
    Q_OBJECT
public:
    explicit MobileBackUp2(QObject *parent = nullptr);
    virtual ~MobileBackUp2();
    mobilebackup2_client_t handle() const;
    mobilebackup2_error_t createMbp2(const Device & device,const lockdownd_service_descriptor_t service);
    mobilebackup2_error_t freeMbp2();
    mobilebackup2_error_t sendRaw(const char * data,uint32_t len,uint32_t *sent);
    mobilebackup2_error_t recvRaw(char * data,uint32_t len,uint32_t * rlen);
    mobilebackup2_error_t versionExchange(double local_versions[], char count, double *remote_version);
    mobilebackup2_error_t sendRequest(const char *request,const char *targetUdid,const char * sourceUdid,plist_t options);
    mobilebackup2_error_t sendMessage(const char *message,plist_t options);
    mobilebackup2_error_t receiveMessage(plist_t *msg,char ** dlmessage);
    mobilebackup2_error_t sendStatusResponse(int statusCode, const char *status1, plist_t status2);
private:
    mobilebackup2_client_t m_mbp2;

};

#endif // MOBILEBACKUP2_H
