/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.4.3
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // C:/Users/41525/Desktop/QT/Qtttttt/lesson5/style.qss
  0x0,0x0,0x0,0x2c,
  0x23,
  0x77,0x69,0x64,0x67,0x65,0x74,0x3a,0x68,0x6f,0x76,0x65,0x72,0x20,0x7b,0xd,0xa,
  0x20,0x20,0x20,0x20,0x63,0x75,0x72,0x73,0x6f,0x72,0x3a,0x20,0x63,0x72,0x6f,0x73,
  0x73,0x68,0x61,0x69,0x72,0x3b,0xd,0xa,0x7d,0xd,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // style.qss
  0x0,0x9,
  0x0,0x28,0xad,0x23,
  0x0,0x73,
  0x0,0x74,0x0,0x79,0x0,0x6c,0x0,0x65,0x0,0x2e,0x0,0x71,0x0,0x73,0x0,0x73,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/style.qss
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x8b,0x9f,0x8a,0x31,0xc2,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qss)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qss)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qss)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qss)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qss)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qss)(); }
   } dummy;
}