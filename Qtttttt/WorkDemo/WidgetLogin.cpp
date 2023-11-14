#include "WidgetLogin.h"
#include "ui_WidgetLogin.h"

#include <QDebug>

WidgetLogin::WidgetLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetLogin)
{
    ui->setupUi(this);
}

WidgetLogin::~WidgetLogin()
{
    delete ui;
}

void WidgetLogin::showError(const QString &msg)
{
    ui->lab_err->setText(msg);
}

void WidgetLogin::clear()
{
    ui->lineEdit_account->setText("");
    ui->lineEdit_pwd->setText("");
    ui->lab_err->setText("");
}

void WidgetLogin::on_pushButton_clicked()
{
    emit login(ui->lineEdit_account->text(), ui->lineEdit_pwd->text());
}

