#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonPhone_6, SIGNAL(clicked()), this, SLOT(showAccountInfo()));

    ui->widget_15->init();
    ui->widget_17->init();
    ui->widget_19->init();
    ui->widget->init();
    ui->widget_11->init();
    ui->widget_5->init();
}

void MainWindow::showAccountInfo()
{
    // 在这里编写显示账户信息的代码
    QString accountInfo = "姓名: 译选\n电话: 15975365478";
    QMessageBox::information(this, "账号信息", accountInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonBuy_6_clicked()
{

}

