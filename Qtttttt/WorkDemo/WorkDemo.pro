QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    WidgetHome.cpp \
    WidgetLogin.cpp \
    WorkBase.cpp \
    WorkHome.cpp \
    WorkLogin.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    WidgetHome.h \
    WidgetLogin.h \
    WorkBase.h \
    WorkHome.h \
    WorkLogin.h

FORMS += \
    MainWindow.ui \
    WidgetHome.ui \
    WidgetLogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
