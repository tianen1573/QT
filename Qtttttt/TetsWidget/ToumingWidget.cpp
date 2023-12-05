#include "ToumingWidget.h"
#include <QPainter>

ToumingWidget::ToumingWidget(QWidget *parent)
    : QWidget{parent}
{}
// void ToumingWidget::paintEvent(QPaintEvent*)
// {
//     QPainter p(this);

//     // 设置透明度
//     qreal opacity = 0.5; // 设置透明度值，范围从 0（完全透明）到 1（完全不透明）
//     p.setOpacity(opacity);

//     // 绘制背景
//     int x = this->x();
//     int y = this->y();
//     int width = this->width();
//     int height = this->height();
//     p.fillRect(x, y, width, height, Qt::green); // 使用指定的颜色填充背景，这里使用绿色作为示例

//     // 绘制其他内容
//     // ...

//     // 绘制完成后，重置透明度
//     p.setOpacity(1.0);
// }
// void ToumingWidget::paintEvent(QPaintEvent*)
// {
//     setAutoFillBackground(false);

//     QPainter p(this);
//     p.setCompositionMode(QPainter::CompositionMode_Clear);
//     int x = this->x();
//     int y = this->y();
//     int width = this->width();
//     int height = this->height();
//     p.fillRect(x, y, width, height, Qt::transparent);
// }
