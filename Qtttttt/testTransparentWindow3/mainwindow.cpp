#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    // 创建阴影效果对象
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(ui->widget_3);
    shadowEffect->setBlurRadius(20); // 设置阴影的模糊半径
    shadowEffect->setColor(Qt::red); // 设置阴影的颜色
    shadowEffect->setOffset(0, 0); // 设置阴影的偏移量

    // 将阴影效果应用于 widget_2
    ui->widget_3->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(),QBrush(QColor(0,0,0,1)));

    QRect widget2Rect = ui->widget_2->rect().translated(ui->widget_2->mapTo(this, QPoint(0, 0)));
    QRect widget3Rect = ui->widget_3->rect().translated(ui->widget_3->mapTo(this, QPoint(0, 0)));
    int radius = 6;
    QColor backGround(255,255,255,255);

    painter.setBrush(backGround); // 设置矩形的填充颜色
    painter.setPen(Qt::transparent); // 设置边框颜色为透明

    // 绘制圆角矩形
    painter.drawRoundedRect(widget2Rect, radius, radius);
    // 填充左下角
    widget2Rect = QRect(ui->widget_2->geometry().x(), ui->widget_2->geometry().y() + ui->widget_2->geometry().height() - radius, radius, radius);
    painter.fillRect(widget2Rect, backGround);
    // 填充右下角
    widget2Rect = QRect(ui->widget_2->geometry().x() + ui->widget_2->geometry().width() - radius,  \
                       ui->widget_2->geometry().y() + ui->widget_2->geometry().height() - radius, radius, radius);
    painter.fillRect(widget2Rect, backGround);

    // 绘制圆角矩形
    painter.drawRoundedRect(widget3Rect, radius, radius);
    // 填充左上角
    widget3Rect.setHeight(radius);
    widget3Rect.setWidth(radius);
    painter.fillRect(widget3Rect, backGround);
    // 填充左下角
    widget3Rect = QRect(widget3Rect.x(), \
                        ui->widget_3->geometry().y() + ui->widget_3->geometry().height() - radius, radius, radius);
    painter.fillRect(widget3Rect, backGround);








//    painter.fillRect(QRect(width() - 50,height() - 50,50,50),QBrush(QColor(0,0,0,1)));
//    painter.fillRect(QRect(0,0,width(),height() - 50),QBrush(QColor(255,0,0,255)));
//    painter.fillRect(QRect(0,height() - 50,width() - 50,50),QBrush(QColor(255,0,0,255)));
}

