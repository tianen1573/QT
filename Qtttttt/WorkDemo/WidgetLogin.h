#ifndef WIDGETLOGIN_H
#define WIDGETLOGIN_H

#include <QWidget>

namespace Ui {
class WidgetLogin;
}

class WidgetLogin : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetLogin(QWidget *parent = nullptr);
    ~WidgetLogin();

    void showError(const QString& msg);

    void clear();
signals:
    void login(const QString& account, const QString& pwd);

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetLogin *ui;
};

#endif // WIDGETLOGIN_H
