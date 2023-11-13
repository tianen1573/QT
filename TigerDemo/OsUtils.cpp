#include "OsUtils.h"
#include <QDir>
#include <QFile>
#include <QString>

OsUtils::OsUtils()
{

}

int OsUtils::osRemoveDirRecursively(const char * path) {
    bool ret = false;
    QString qpath = QString::fromUtf8(path);
    QDir dir(qpath);
    if (dir.exists()) {
        ret = dir.removeRecursively();
    } else { // 不存在，认为删除成功
        return 0;
    }
    if(ret)
        return 0;

    return -1;
}

int OsUtils::osRemoveFile(const char * path) {
    bool ret = false;
    QString qpath = QString::fromUtf8(path);
    QFile file(qpath);
    if (file.exists()) {
        ret = file.remove();
    } else{ // 不存在，认为删除成功，也可以返回ENOENT(c)
        return 0;
    }

    if (ret)
        return 0;

    return -1;
}

int OsUtils::osRename(const char * oldpath,const char * newpath) {

    QFile file(oldpath);
    if(file.rename(newpath))
    {
        return 0;
    }
    // 对应的标准库rename的失败错误码有很多种，这里仅仅使用表示操作失误的-1

    return -1;
}

int OsUtils::osMkdir(const char *path, int mode){
    QDir dir;
    if(dir.mkdir(path)){
        return 0;
    }
    // 默认继承父目录的权限
    // QT的文件权限和标准库的不同，如果希望使用mode，需要进行转换

    return -1;
}

int OsUtils::osMkdirWithParents(const char *path, int mode)
{
    QDir dir;
    if(dir.exists(path))
    {
        return 0;
    }
    if(dir.mkpath(path))
    {
        return 0;
    }

    return -1;
}
