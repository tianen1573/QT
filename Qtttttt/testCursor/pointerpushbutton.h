#ifndef POINTERPUSHBUTTON_H
#define POINTERPUSHBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>

class PointerPushButton : public QPushButton
{
    Q_OBJECT
public:
    PointerPushButton(QWidget *parent = nullptr);
};

#endif // POINTERPUSHBUTTON_H
