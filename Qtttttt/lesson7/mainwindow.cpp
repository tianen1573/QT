#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    QObject::connect(this, &MainWindow::UpdateProgress, this, &MainWindow::onUpdateOverallProgress);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onStartTest()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdateOverallProgress(int p)
{
    ui->progressBar->setValue(p);
    QCoreApplication::processEvents();
}

void MainWindow::onStartTest()
{
    QThread::msleep(100);
    emit UpdateProgress(90);
    QThread::msleep(100);
    emit UpdateProgress(20);
    QThread::msleep(100);
    emit UpdateProgress(30);
    QThread::msleep(100);
    emit UpdateProgress(40);
    QThread::msleep(100);
    emit UpdateProgress(90);
    QThread::msleep(100);
    emit UpdateProgress(80);
    QThread::msleep(100);
}

