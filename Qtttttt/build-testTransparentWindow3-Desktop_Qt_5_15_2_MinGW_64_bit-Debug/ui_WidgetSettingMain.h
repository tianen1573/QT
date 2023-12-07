/********************************************************************************
** Form generated from reading UI file 'WidgetSettingMain.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETSETTINGMAIN_H
#define UI_WIDGETSETTINGMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetSettingMain
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QListView *listView;

    void setupUi(QWidget *WidgetSettingMain)
    {
        if (WidgetSettingMain->objectName().isEmpty())
            WidgetSettingMain->setObjectName(QString::fromUtf8("WidgetSettingMain"));
        WidgetSettingMain->resize(400, 600);
        WidgetSettingMain->setMinimumSize(QSize(400, 600));
        verticalLayout = new QVBoxLayout(WidgetSettingMain);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTitle = new QWidget(WidgetSettingMain);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        widgetTitle->setMinimumSize(QSize(400, 80));
        horizontalLayout = new QHBoxLayout(widgetTitle);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widgetTitle);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widgetTitle);

        listView = new QListView(WidgetSettingMain);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(400, 520));

        verticalLayout->addWidget(listView);


        retranslateUi(WidgetSettingMain);

        QMetaObject::connectSlotsByName(WidgetSettingMain);
    } // setupUi

    void retranslateUi(QWidget *WidgetSettingMain)
    {
        WidgetSettingMain->setWindowTitle(QCoreApplication::translate("WidgetSettingMain", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetSettingMain", "SETTING", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetSettingMain: public Ui_WidgetSettingMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETSETTINGMAIN_H
