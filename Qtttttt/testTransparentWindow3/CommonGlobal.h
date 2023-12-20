#ifndef COMMONGLOBAL_H
#define COMMONGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TIGERDR_COMMON_LIBRARY)
#  define TIGERDR_COMMON_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define TIGERDR_COMMON_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMONGLOBAL_H