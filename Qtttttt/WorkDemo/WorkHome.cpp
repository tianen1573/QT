#include "WorkHome.h"

#include "WidgetHome.h"

WorkHome::WorkHome(QStackedWidget* stackwidget, QObject *parent)
    :WorkBase(stackwidget, parent)
{
    m_widgetHome = new WidgetHome();

    connect(m_widgetHome, &WidgetHome::logout, this, &WorkHome::onLogout);
}

WorkHome::~WorkHome()
{

}

void WorkHome::start()
{
    this->stackedRemovceAll();
    this->m_stackWidget->addWidget(m_widgetHome);
}

void WorkHome::onLogout()
{
    emit back();
}
