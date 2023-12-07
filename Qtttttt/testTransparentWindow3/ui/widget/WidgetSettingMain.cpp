#include "WidgetSettingMain.h"
#include "ui_WidgetSettingMain.h"

WidgetSettingMain::WidgetSettingMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetSettingMain)
{
    ui->setupUi(this);
}

WidgetSettingMain::~WidgetSettingMain()
{
    delete ui;
}
