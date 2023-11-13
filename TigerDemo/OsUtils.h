#ifndef OSUTILS_H
#define OSUTILS_H

#include <QObject>

class OsUtils
{
public:
    OsUtils();

    static int osRemoveDirRecursively(const char * path);
    static int osRemoveFile(const char * path);
    static int osRename(const char * oldpath,const char * newpath);
    static int osMkdir(const char* path, int mode);
    static int osMkdirWithParents(const char * dir, int mode);
};

#endif // OSUTILS_H
