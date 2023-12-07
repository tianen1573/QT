#ifndef WIDGETSETTINGMAIN_H
#define WIDGETSETTINGMAIN_H

#include <QWidget>

namespace Ui {
class WidgetSettingMain;
}

class WidgetSettingMain : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSettingMain(QWidget *parent = nullptr);
    ~WidgetSettingMain();

private:
    Ui::WidgetSettingMain *ui;
};

#endif // WIDGETSETTINGMAIN_H
