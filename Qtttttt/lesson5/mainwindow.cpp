#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::showAccountInfo()
{
    // 在这里编写显示账户信息的代码
    QString accountInfo = "Account Name: John Doe\nAccount Number: 123456789";
    QMessageBox::information(this, "Account Info", accountInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

