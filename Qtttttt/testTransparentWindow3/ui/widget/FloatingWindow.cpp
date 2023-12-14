#include "FloatingWindow.h"
#include "ui_FloatingWindow.h"

#include <QGuiApplication>
#include <QScreen>


#include <QDebug>

FloatingWindow::FloatingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatingWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        // 设置窗口的属性：
        // - Qt::FramelessWindowHint：去掉窗口的边框
        // - Qt::WindowStaysOnTopHint：窗口保持在最顶层
        // - Qt::Tool：将窗口作为工具窗口，不在任务栏显示
}

FloatingWindow::~FloatingWindow()
{
    delete ui;
}

void FloatingWindow::on_btn_full_clicked()
{
    emit checkFull();
}

