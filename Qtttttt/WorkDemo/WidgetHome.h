#ifndef WIDGETHOME_H
#define WIDGETHOME_H

#include <QWidget>

namespace Ui {
class WidgetHome;
}

class WidgetHome : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetHome(QWidget *parent = nullptr);
    ~WidgetHome();

signals:
    void logout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetHome *ui;
};

#endif // WIDGETHOME_H
