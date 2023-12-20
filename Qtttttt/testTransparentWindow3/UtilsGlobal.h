#ifndef UTILSGLOBAL_H
#define UTILSGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UTILS_LIBRARY)
#  define UTILS_EXPORT Q_DECL_EXPORT
#else
#  define UTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // UTILSGLOBAL_H
