#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(QRect(width() - 50,height() - 50,50,50),QBrush(QColor(0,0,0,1)));
    painter.fillRect(QRect(0,0,width(),height() - 50),QBrush(QColor(255,0,0,255)));
    painter.fillRect(QRect(0,height() - 50,width() - 50,50),QBrush(QColor(255,0,0,255)));
}

