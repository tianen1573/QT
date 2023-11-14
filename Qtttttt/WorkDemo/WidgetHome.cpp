#include "WidgetHome.h"
#include "ui_WidgetHome.h"

WidgetHome::WidgetHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetHome)
{
    ui->setupUi(this);
}

WidgetHome::~WidgetHome()
{
    delete ui;
}

void WidgetHome::on_pushButton_clicked()
{
    emit logout();
}

