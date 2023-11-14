#include "AFC.h"

AFC::AFC(QObject *parent)
    : QObject{parent}, m_afc(nullptr)
{

}

AFC::~AFC()
{

}

afc_client_t AFC::getAFC() const
{
    return m_afc;
}

afc_error_t AFC::createAFC(const Device &device, const lockdownd_service_descriptor_t service)
{
    if(m_afc)
        freeAFC();

    return afc_client_new(device.getIdevice(), service, &m_afc);
}

afc_error_t AFC::freeAFC()
{
    auto errRet = afc_client_free(m_afc);
    m_afc = nullptr;

    return errRet;
}

afc_error_t AFC::openFile(const char *fileName, afc_file_mode_t fileMode, uint64_t *fileHandle)
{
    return afc_file_open(m_afc, fileName, fileMode, fileHandle);
}

afc_error_t AFC::closeFile(uint64_t fileHandle)
{
    return afc_file_close(m_afc, fileHandle);
}

void AFC::readFile(const char *fileName, char **data, uint64_t *size)
{
    if (!m_afc || !data || !size) {
        return ;
    }

    char **fileinfo = NULL;
    uint32_t fsize = 0;

    afc_get_file_info(m_afc, fileName, &fileinfo);
    if (!fileinfo) {
        return ;
    }
    int i;
    for (i = 0; fileinfo[i]; i += 2) {
        if (!strcmp(fileinfo[i], "st_size")) {
            fsize = atol(fileinfo[i + 1]);
            break;
        }
    }
    afc_dictionary_free(fileinfo);

    if (fsize == 0) {
        return;
    }

    uint64_t f = 0;
    afc_file_open(m_afc, fileName, AFC_FOPEN_RDONLY, &f);
    if (!f) {
        return ;
    }
    char *buf = (char*)malloc((uint32_t)fsize);
    uint32_t done = 0;
    while (done < fsize) {
        uint32_t bread = 0;
        afc_file_read(m_afc, f, buf+done, 65536, &bread);
        if (bread > 0) {
            done += bread;
        } else {
            break;
        }
    }
    if (done == fsize) {
        *size = fsize;
        *data = buf;
    } else {
        free(buf);
    }
    afc_file_close(m_afc, f);
    return ;
}

afc_error_t AFC::lockFile(uint64_t fileHanle, afc_lock_op_t operation)
{
    return afc_file_lock(m_afc,fileHanle,operation);
}

