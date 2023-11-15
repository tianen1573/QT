#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IdeviceId.h"
#include "IdevicePair.h"
#include "IdeviceBackUp.h"
#include "DeviceBackUp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    IdeviceId *id = new IdeviceId();
    IdevicePair *pair = new IdevicePair();
    IdeviceBackUp *bp = new IdeviceBackUp();
    DeviceBackUp *backup = new DeviceBackUp();

    QObject::connect(bp, &IdeviceBackUp::updateBar, this, &MainWindow::onUpdateBar);
    QObject::connect(id, &IdeviceId::updateTxt, this, &MainWindow::onUpdateTxt);
    QObject::connect(ui->IdeviceIdPushBtn, SIGNAL(clicked()), id, SLOT(SelectId()));
    QObject::connect(ui->IdeviceNamePushBtn, SIGNAL(clicked()), id, SLOT(SelectName()));
    QObject::connect(ui->IdevicePairPushBtn, SIGNAL(clicked()), pair, SLOT(DevicePair()));
//    QObject::connect(ui->IdeviceBackupPushBtn, SIGNAL(clicked()), bp, SLOT(start()));
//    QObject::connect(ui->pushButton, SIGNAL(clicked()), bp, SLOT(stop()));
    QObject::connect(backup,  &DeviceBackUp::setProgressBar, this, &MainWindow::onUpdateBar);
    QObject::connect(ui->IdeviceBackupPushBtn, SIGNAL(clicked()), backup, SLOT(start()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()), backup, SLOT(stop()));
    QObject::connect(backup, &DeviceBackUp::logShow, this, &MainWindow::onUpdateTxt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdateTxt(const QString &txt)
{
    ui->textEdit->append(txt);
}

void MainWindow::onUpdateBar(int p)
{
    ui->progressBar->setValue(p);
    QCoreApplication::processEvents();
}

