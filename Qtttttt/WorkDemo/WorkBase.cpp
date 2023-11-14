#include "WorkBase.h"

WorkBase::WorkBase(QStackedWidget* stackwidget, QObject *parent)
    : QObject{parent}
{
    this->m_stackWidget = stackwidget;
}

void WorkBase::stackedRemovceAll()
{
    if(this->m_stackWidget != nullptr) {
        for(int i = m_stackWidget->count(); i >= 0; i--)
        {
            QWidget* widget = m_stackWidget->widget(i);
            m_stackWidget->removeWidget(widget);
            //            delete widget;
        }
    }
}
