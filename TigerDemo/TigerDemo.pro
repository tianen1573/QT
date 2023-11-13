QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    DEBUG_OR_RELEASE = debug
}  else {
    DEBUG_OR_RELEASE = release
}

# 加载库
# thirdparty libraries
include($$PWD/../thirdparty/thirdparty.pri)
SOURCES += \
    FileToolsBackUp.cpp \
    IdeviceBackUp.cpp \
    IdeviceId.cpp \
    IdevicePair.cpp \
    OsUtils.cpp \
    Test.c \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FileToolsBackUp.h \
    IdeviceBackUp.h \
    IdeviceId.h \
    IdevicePair.h \
    OsUtils.h \
    endianness.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
