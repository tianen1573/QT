#ifndef WORKHOME_H
#define WORKHOME_H

#include "WorkBase.h"

class WidgetHome;

class WorkHome : public WorkBase
{
    Q_OBJECT
public:
    WorkHome(QStackedWidget* stackwidget, QObject *parent = nullptr);

    virtual ~WorkHome();

public:
    void start();

public slots:
    void onLogout();

private:
    WidgetHome* m_widgetHome;
};

#endif // WORKHOME_H
