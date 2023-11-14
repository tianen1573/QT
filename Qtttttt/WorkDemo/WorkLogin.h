#ifndef WORKLOGIN_H
#define WORKLOGIN_H

#include <QObject>

#include "WidgetLogin.h"
#include "WorkBase.h"

class WorkLogin : public WorkBase
{
    Q_OBJECT
public:
    explicit WorkLogin(QStackedWidget* stackwidget, QObject *parent = nullptr);

    virtual ~WorkLogin();

    void start();

public slots:
    void onLogin(const QString& account, const QString& pwd);

private:
    WidgetLogin* m_widgetLogin;
};

#endif // WORKLOGIN_H
