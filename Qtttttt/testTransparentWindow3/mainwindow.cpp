#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include "ui/widget/WidgetSettingMain.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // 透明+无边框
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


    ui->stackedMainWidget->removeWidget(ui->widgetSetting);

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

    QRect widgetBody = ui->widgetBody->rect().translated(ui->widgetBody->mapTo(this, QPoint(0, 0)));
    QRect widgetNav = ui->widgetNav->rect().translated(ui->widgetNav->mapTo(this, QPoint(0, 0)));
    int radius = 6;
    QColor backGround(255,255,255,255);

    painter.setBrush(backGround); // 设置矩形的填充颜色
    painter.setPen(Qt::transparent); // 设置边框颜色为透明

    // 绘制圆角矩形
    painter.drawRoundedRect(widgetBody, radius, radius);
    // 填充左下角
    widgetBody = QRect(ui->widgetBody->geometry().x(), ui->widgetBody->geometry().y() + ui->widgetBody->geometry().height() - radius, radius, radius);
    painter.fillRect(widgetBody, backGround);
    // 填充右下角
    widgetBody = QRect(ui->widgetBody->geometry().x() + ui->widgetBody->geometry().width() - radius,  \
                       ui->widgetBody->geometry().y() + ui->widgetBody->geometry().height() - radius, radius, radius);
    painter.fillRect(widgetBody, backGround);

    // 绘制圆角矩形
    painter.drawRoundedRect(widgetNav, radius, radius);
    // 填充左上角
    widgetNav.setHeight(radius);
    widgetNav.setWidth(radius);
    painter.fillRect(widgetNav, backGround);
    // 填充左下角
    widgetNav = QRect(widgetNav.x(), \
                        widgetNav.y() + ui->widgetNav->height() - radius, radius, radius);
    painter.fillRect(widgetNav, backGround);
}

