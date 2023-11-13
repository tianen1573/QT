#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IdeviceId.h"
#include "IdevicePair.h"
#include "IdeviceBackUp.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    IdeviceId *id = new IdeviceId();

    connect(id, &IdeviceId::updateTxt, this, &MainWindow::onUpdateTxt);

    IdevicePair *pair = new IdevicePair();
    IdeviceBackUp *bp = new IdeviceBackUp();
    QObject::connect(ui->IdeviceIdPushBtn, SIGNAL(clicked()), id, SLOT(SelectId()));
    QObject::connect(ui->IdeviceNamePushBtn, SIGNAL(clicked()), id, SLOT(SelectName()));
    QObject::connect(ui->IdevicePairPushBtn, SIGNAL(clicked()), pair, SLOT(DevicePair()));
    QObject::connect(ui->IdeviceBackupPushBtn, SIGNAL(clicked()), bp, SLOT(BackUp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdateTxt(const QString &txt)
{
    ui->textEdit->append(txt);
}

