#include "WidgetSettingMain.h"
#include "ui_WidgetSettingMain.h"

WidgetSettingMain::WidgetSettingMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetSettingMain)
{
    ui->setupUi(this);


    ui->btn_test;
}

WidgetSettingMain::~WidgetSettingMain()
{
    delete ui;
}
