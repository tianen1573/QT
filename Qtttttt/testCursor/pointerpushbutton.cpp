#include "pointerpushbutton.h"
#include <QCursor>


PointerPushButton::PointerPushButton(QWidget *parent):
    QPushButton(parent)
{
    QCursor pointingHandCursor(Qt::PointingHandCursor);
    setCursor(pointingHandCursor);
}
