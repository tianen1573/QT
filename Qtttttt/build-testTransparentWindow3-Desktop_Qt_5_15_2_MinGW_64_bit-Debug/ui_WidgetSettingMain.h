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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetSettingMain
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_test_5;
    QPushButton *btn_test_4;
    QPushButton *btn_test_3;
    QPushButton *btn_test_2;
    QPushButton *btn_test;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *WidgetSettingMain)
    {
        if (WidgetSettingMain->objectName().isEmpty())
            WidgetSettingMain->setObjectName(QString::fromUtf8("WidgetSettingMain"));
        WidgetSettingMain->resize(400, 600);
        WidgetSettingMain->setMinimumSize(QSize(400, 600));
        WidgetSettingMain->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 181, 181);"));
        horizontalLayout_2 = new QHBoxLayout(WidgetSettingMain);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        widget_2 = new QWidget(WidgetSettingMain);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTitle = new QWidget(widget_2);
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

        widget = new QWidget(widget_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_test_5 = new QPushButton(widget);
        btn_test_5->setObjectName(QString::fromUtf8("btn_test_5"));
        btn_test_5->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(btn_test_5);

        btn_test_4 = new QPushButton(widget);
        btn_test_4->setObjectName(QString::fromUtf8("btn_test_4"));
        btn_test_4->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(btn_test_4);

        btn_test_3 = new QPushButton(widget);
        btn_test_3->setObjectName(QString::fromUtf8("btn_test_3"));
        btn_test_3->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(btn_test_3);

        btn_test_2 = new QPushButton(widget);
        btn_test_2->setObjectName(QString::fromUtf8("btn_test_2"));
        btn_test_2->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(btn_test_2);

        btn_test = new QPushButton(widget);
        btn_test->setObjectName(QString::fromUtf8("btn_test"));
        btn_test->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(btn_test);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(widget);


        horizontalLayout_2->addWidget(widget_2);

        horizontalSpacer_4 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        retranslateUi(WidgetSettingMain);

        QMetaObject::connectSlotsByName(WidgetSettingMain);
    } // setupUi

    void retranslateUi(QWidget *WidgetSettingMain)
    {
        WidgetSettingMain->setWindowTitle(QCoreApplication::translate("WidgetSettingMain", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetSettingMain", "SETTING", nullptr));
        btn_test_5->setText(QCoreApplication::translate("WidgetSettingMain", "PushButton", nullptr));
        btn_test_4->setText(QCoreApplication::translate("WidgetSettingMain", "PushButton", nullptr));
        btn_test_3->setText(QCoreApplication::translate("WidgetSettingMain", "PushButton", nullptr));
        btn_test_2->setText(QCoreApplication::translate("WidgetSettingMain", "PushButton", nullptr));
        btn_test->setText(QCoreApplication::translate("WidgetSettingMain", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetSettingMain: public Ui_WidgetSettingMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETSETTINGMAIN_H
