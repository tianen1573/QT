#ifndef WIDGETTESTCENTER_H
#define WIDGETTESTCENTER_H

#include <QWidget>

namespace Ui {
class WidgetTestCenter;
}

class WidgetTestCenter : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTestCenter(QWidget *parent = nullptr);
    ~WidgetTestCenter();

private:
    Ui::WidgetTestCenter *ui;
};

#endif // WIDGETTESTCENTER_H
