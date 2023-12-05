#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPalette>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    // QPalette pal = palette();
    // ui->widget_2->setAttribute(Qt::WA_TranslucentBackground);
    // ui->widget_2->setAttribute(Qt::WA_NoSystemBackground);
    // pal.setColor(QPalette::Background, QColor(0x00, 0xFF, 0x00, 0x88));
    // ui->widget_2->setPalette(pal);
    // ui->widget_2->update();


    // ui->widget->setWindowOpacity(0);
    // this->setWindowOpacity(0.005);
    // ui->widget_2->setWindowOpacity(0);
    // setWindowOpacity(0.005);
    // this->setAttribute(Qt::WA_WState_WindowOpacitySet);
    // setAttribute(Qt::WA_NoSystemBackground);
    // this->setWindowOpacity(0.005);
    // ui->centralwidget->setWindowOpacity(0.5);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00, 0xFF, 0x00, 0x00));
    ui->widget->setPalette(pal);
    // ui->widget->update();
    // ui->widget->setAttribute(Qt::WA_TranslucentBackground, true);
    // ui->widget->setWindowOpacity(0);

    // this->setWindowFlags(Qt::FramelessWindowHint);
    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // this->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

