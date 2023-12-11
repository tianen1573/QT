#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <cmath>
#include <QDebug>

#include "ui/widget/WidgetSettingMain.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // 透明+无边框
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    // // 创建阴影效果对象
    // QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    // shadowEffect->setBlurRadius(10); // 设置阴影的模糊半径
    // shadowEffect->setColor(Qt::red); // 设置阴影的颜色
    // shadowEffect->setOffset(0, 0); // 设置阴影的偏移量
    // // 将阴影效果应用于 主窗口，此时阴影效果将作用在主窗口所在区域，最底层的且最先有颜色的位置
    // this->setGraphicsEffect(shadowEffect);

    // ui->stackedMainWidget->removeWidget(ui->widgetSetting);

}

MainWindow::~MainWindow()
{
    delete ui;
}

double normalDistribution(double x) {
    double mean = 0.0;  // 均值
    double stdDev = 4.0;  // 标准差
    double exponent = -0.5 * pow((x - mean) / stdDev, 2);
    double coefficient = 255.0 / exp(-0.5 * pow(mean / stdDev, 2));

    double y = coefficient * exp(exponent);
    return y;
}

// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);
//     painter.fillRect(rect(),QBrush(QColor(0,0,0,1)));

//     QRect widgetBody = ui->widgetBody->rect().translated(ui->widgetBody->mapTo(this, QPoint(0, 0)));
//     QRect widgetNav = ui->widgetNav->rect().translated(ui->widgetNav->mapTo(this, QPoint(0, 0)));
//     int radius = 10;
//     QColor backGround(255,255,255,255);

//     QRect leftRect(widgetBody.x() - 10, widgetBody.y() - 10, widgetBody.width() + 20, widgetBody.height() + 20);
//     QRect rigRect(widgetNav.x() - 10, widgetNav.y() - 10, widgetNav.width() + 20, widgetNav.height() + 20);
//     // QRect leftRect(widgetBody.x() - 5, widgetBody.y() - 5, widgetBody.width() + 10, widgetBody.height() + 10);
//     // QRect rigRect(widgetNav.x() - 5, widgetNav.y() - 5, widgetNav.width() + 10, widgetNav.height() + 10);
//     QPainterPath leftPath, rigPath;
//     leftPath.addRoundedRect(leftRect, radius + 5, radius + 5);
//     rigPath.addRoundedRect(rigRect, radius + 5, radius + 5);

//     QPainterPath mergedPath = leftPath.united(rigPath);

//     painter.setPen(Qt::transparent); // 设置边框颜色为透明
//     for(int i = 0; i < 10; ++ i)
//     {
//         // 创建新的 QPainterPath，用于缩小
//         int alpha = (int)normalDistribution(13 - i);
//         QColor color(168, 168, 168, alpha);

//         QPainterPath shrinkPath;
//         QPainterPathStroker stroker;
//         stroker.setWidth(-1.0);  // 将线宽设置为 -1，表示缩小 1 像素
//         shrinkPath = stroker.createStroke(mergedPath);
//         mergedPath = mergedPath.subtracted(shrinkPath);
//         painter.setPen(color);

//         QRectF boundingRect = mergedPath.boundingRect();
//         qDebug() << boundingRect.width() << boundingRect.height();

//         if(i == 0){
//             painter.setPen(Qt::blue);
//             painter.drawPath(mergedPath);
//         } else if(i == 9){
//             painter.setPen(Qt::red);
//             painter.drawPath(mergedPath);
//             painter.fillPath(mergedPath, backGround);
//         } else {
//             // painter.fillPath(mergedPath, color);
//             painter.drawPath(mergedPath);
//         }
//     }
//     // for(int i = 0; i < 6; ++ i)
//     // {
//     //     // 创建新的 QPainterPath，用于缩小
//     //     int alpha = (int)normalDistribution(9 - i);
//     //     QColor color(168, 168, 168, alpha);
//     //     qDebug() << alpha;
//     //     QPainterPath shrinkPath;
//     //     QPainterPathStroker stroker;
//     //     // stroker.setWidth(-2.0);  // 将线宽设置为 -1，表示缩小 1 像素
//     //     shrinkPath = stroker.createStroke(mergedPath);
//     //     mergedPath = mergedPath.subtracted(shrinkPath);
//     //     shrinkPath = stroker.createStroke(mergedPath);
//     //     mergedPath = mergedPath.subtracted(shrinkPath);
//     //     painter.setPen(color);

//     //     // QRectF boundingRect = mergedPath.boundingRect();
//     //     // qDebug() << boundingRect.width() << boundingRect.height();
//     //     if(i == 0){
//     //         painter.setPen(Qt::blue);
//     //         painter.drawPath(mergedPath);
//     //     }
//     //     else if(i == 5){
//     //         painter.setPen(Qt::red);
//     //         painter.drawPath(mergedPath);
//     //         painter.fillPath(mergedPath, backGround);
//     //     }else {
//     //         // painter.fillPath(mergedPath, color);
//     //         painter.drawPath(mergedPath);
//     //     }
//     // }

//     // painter.setBrush(backGround); // 设置矩形的填充颜色
//     // painter.setPen(Qt::transparent); // 设置边框颜色为透明
//     // // 绘制圆角矩形
//     // painter.drawRoundedRect(widgetBody, radius, radius);
//     // // 填充左下角
//     // widgetBody = QRect(ui->widgetBody->geometry().x(), ui->widgetBody->geometry().y() + ui->widgetBody->geometry().height() - radius, radius, radius);
//     // painter.fillRect(widgetBody, backGround);
//     // // 填充右下角
//     // widgetBody = QRect(ui->widgetBody->geometry().x() + ui->widgetBody->geometry().width() - radius,  \
//     //                    ui->widgetBody->geometry().y() + ui->widgetBody->geometry().height() - radius, radius, radius);
//     // painter.fillRect(widgetBody, backGround);
//     // // 绘制圆角矩形
//     // painter.drawRoundedRect(widgetNav, radius, radius);
//     // // 填充左上角
//     // widgetNav.setHeight(radius);
//     // widgetNav.setWidth(radius);
//     // painter.fillRect(widgetNav, backGround);
//     // // 填充左下角
//     // widgetNav = QRect(widgetNav.x(), \
//     //                                      widgetNav.y() + ui->widgetNav->height() - radius, radius, radius);
//     // painter.fillRect(widgetNav, backGround);

// }


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(),QBrush(QColor(0,0,0,1)));

    QRect widgetBody = ui->widgetBody->rect().translated(ui->widgetBody->mapTo(this, QPoint(0, 0)));
    QRect widgetNav = ui->widgetNav->rect().translated(ui->widgetNav->mapTo(this, QPoint(0, 0)));
    QColor backGround(255,255,255,255);

    for(int i = 10; i >= 0; -- i)
    {
        QRect leftRect(widgetBody.x() - i, widgetBody.y() - i, widgetBody.width() + i * 2, widgetBody.height() + i * 2);
        QRect rigRect(widgetNav.x() - i - 5, widgetNav.y() - i, widgetNav.width() + i * 2 + 5, widgetNav.height() + i * 2);
        QPainterPath leftPath, rigPath;
        leftPath.addRoundedRect(leftRect, i + 5, i + 5);
        rigPath.addRoundedRect(rigRect, i + 5, i + 5);
        QPainterPath mergedPath = leftPath.united(rigPath);

        int alpha = (int)normalDistribution(i + 3);
        QColor color(168, 168, 168, alpha);

        painter.setPen(color);
        if(i == 10)
            painter.setPen(Qt::red);
        if(i == 0)
            painter.setPen(Qt::blue);
        painter.drawPath(mergedPath);
        if(i == 0)
            painter.fillPath(mergedPath, backGround);
    }
}
