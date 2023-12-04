#include "pointerqwidget.h"

#include <QStyleOption>
#include <QPainter>

PointerQWidget::PointerQWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("PointerQWidget");
    QCursor pointingHandCursor(Qt::PointingHandCursor);
    setCursor(pointingHandCursor);

    setAttribute(Qt::WA_StyledBackground);
}

void PointerQWidget::init()
{
    setStyleSheet("background: red;box-shadow: 0px 4px 19px 0px #E8ECFF;border-radius: 6px");
}

void PointerQWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,
                           &opt,&painter,this);
}
