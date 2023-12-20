#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
//    QCoreApplication::setAttribute(Qt::AA_NativeWindows);

    ////////////////////////////////////////////
    /// 请勿随意改动一下初始化代码的顺序
    // 高DPI支持
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

//    patchIntelBraphicsBug();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
