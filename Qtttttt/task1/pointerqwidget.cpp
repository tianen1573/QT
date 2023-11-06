#include "pointerqwidget.h"

PointerQWidget::PointerQWidget(QWidget *parent)
    : QWidget(parent)
{
    QCursor pointingHandCursor(Qt::PointingHandCursor);
    setCursor(pointingHandCursor);
    setAttribute(Qt::WA_StyledBackground);
}

void PointerQWidget::init()
{
    setStyleSheet("background: #FFFFFF;box-shadow: 0px 4px 19px 0px #E8ECFF;border-radius: 6px");
}
