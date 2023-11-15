#ifndef AFC_H
#define AFC_H

#include <QObject>
#include <libimobiledevice/afc.h>
#include "Device.h"

/*
 * 连接设备的AFC服务
 * 创建AFC服务客户端对象，释放客户端对象
 * 通过AFC：打开文件、关闭文件、读取文件、锁定文件
*/
class AFC : public QObject
{
    Q_OBJECT
public:
    explicit AFC(QObject *parent = nullptr);
    virtual ~AFC();
    afc_client_t getAFC() const;

    afc_error_t openAFC(const Device& device, const lockdownd_service_descriptor_t service);
    afc_error_t closeAFC();
    afc_error_t openFile(const char* fileName, afc_file_mode_t fileMode, uint64_t* fileHandle);
    afc_error_t closeFile(uint64_t fileHandle);
    void readFile(const char *fileName, char **data, uint64_t *size);
    afc_error_t lockFile(uint64_t fileHanle, afc_lock_op_t operation);
private:
    afc_client_t m_afc;

};

#endif // AFC_H
