#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NetWork.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    NetWork* network = new NetWork;

    connect(ui->pushButton, SIGNAL(clicked()), network, SLOT(onStartDownload()));
    connect(network, &NetWork::setProgressBarVal, this, &MainWindow::onSetProgressBarVal);
    connect(network, &NetWork::displayFinishedWidget, this, &MainWindow::onDisplayFinishedWidget);
    connect(network, &NetWork::setPushButtonEnabled, this, &MainWindow::onSetPushButtonEnabled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetProgressBarVal(int p)
{
    ui->progressBar->setValue(p);
    QCoreApplication::processEvents();
}

void MainWindow::onDisplayFinishedWidget(const QString &desc)
{
    QMessageBox::information(this,"Finished", desc);
}

void MainWindow::onSetPushButtonEnabled(bool flag)
{
    ui->pushButton->setEnabled(flag);
}
