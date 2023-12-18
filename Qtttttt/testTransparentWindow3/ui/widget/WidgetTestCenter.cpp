#include "WidgetTestCenter.h"
#include "ui_WidgetTestCenter.h"

WidgetTestCenter::WidgetTestCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTestCenter)
{
    ui->setupUi(this);
}

WidgetTestCenter::~WidgetTestCenter()
{
    delete ui;
}
