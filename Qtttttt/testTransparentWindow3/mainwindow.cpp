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
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10); // 设置阴影的模糊半径
    shadowEffect->setColor(Qt::red); // 设置阴影的颜色
    shadowEffect->setOffset(0, 0); // 设置阴影的偏移量
    // 将阴影效果应用于 主窗口，此时阴影效果将作用在主窗口所在区域，最底层的且最先有颜色的位置
    this->setGraphicsEffect(shadowEffect);

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
                        widget3Rect.y() + ui->widget_3->height() - radius, radius, radius);
    painter.fillRect(widget3Rect, backGround);
}

