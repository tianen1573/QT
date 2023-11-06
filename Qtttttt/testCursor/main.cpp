#include "mainwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建一个样式表文件
    QFile styleFile(":/style.qss"); // 样式表文件的路径
    // 打开样式表文件
    if (styleFile.open(QFile::ReadOnly)) {
        // 加载样式表内容
        QString styleSheet = QLatin1String(styleFile.readAll());

        // 设置样式表
        a.setStyleSheet(styleSheet);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
