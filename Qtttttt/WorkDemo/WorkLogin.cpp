#include "WorkLogin.h"

WorkLogin::WorkLogin(QStackedWidget* stackwidget, QObject *parent)
    : WorkBase{stackwidget, parent}
{
    m_widgetLogin = new WidgetLogin;

    connect(m_widgetLogin, &WidgetLogin::login, this, &WorkLogin::onLogin);
}

WorkLogin::~WorkLogin()
{

}

void WorkLogin::start()
{
    this->stackedRemovceAll();
    m_widgetLogin->clear();
    this->m_stackWidget->addWidget(m_widgetLogin);
}

void WorkLogin::onLogin(const QString &account, const QString &pwd)
{
    if(account.isEmpty()) {
        m_widgetLogin->showError("account is empty");
        return;
    }

    if(pwd.isEmpty()) {
        m_widgetLogin->showError("pwd is empty");
        return;
    }

    if(account == "ycy" && pwd == "123456") {
        emit next();
    } else {
        emit back();
    }
}
