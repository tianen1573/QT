QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui/widget/FloatingWindow.cpp \
    ui/widget/WidgetSettingMain.cpp \
    ui/widget/WidgetTestCenter.cpp

HEADERS += \
    mainwindow.h \
    ui/widget/FloatingWindow.h \
    ui/widget/WidgetSettingMain.h \
    ui/widget/WidgetTestCenter.h

FORMS += \
    mainwindow.ui \
    ui/widget/FloatingWindow.ui \
    ui/widget/WidgetSettingMain.ui \
    ui/widget/WidgetTestCenter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
