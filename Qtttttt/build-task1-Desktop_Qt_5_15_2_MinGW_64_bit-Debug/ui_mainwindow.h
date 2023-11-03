/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_24;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer_53;
    QLabel *label_logo_6;
    QSpacerItem *horizontalSpacer_54;
    QWidget *widgetUP_2;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_10;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_46;
    QPushButton *pushButtonBuy_6;
    QSpacerItem *horizontalSpacer_47;
    QPushButton *pushButtonAccount_6;
    QSpacerItem *horizontalSpacer_48;
    QPushButton *pushButtonPhone_6;
    QSpacerItem *horizontalSpacer_49;
    QPushButton *pushButtonSetting_6;
    QSpacerItem *horizontalSpacer_50;
    QWidget *widget;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose_11;
    QSpacerItem *horizontalSpacer_51;
    QPushButton *pushButtonClose_12;
    QSpacerItem *horizontalSpacer_52;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_9;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_11;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_10;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget_14;
    QSpacerItem *horizontalSpacer_8;
    QWidget *widget_15;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(false);
        MainWindow->resize(1036, 657);
        MainWindow->setMinimumSize(QSize(1024, 615));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_5 = new QWidget(centralwidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(1024, 54));
        widget_5->setMaximumSize(QSize(16777215, 54));
        horizontalLayout_24 = new QHBoxLayout(widget_5);
        horizontalLayout_24->setSpacing(0);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(0, 0, 0, 0);
        widget_7 = new QWidget(widget_5);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setMinimumSize(QSize(390, 0));
        widget_7->setMaximumSize(QSize(390, 16777215));
        horizontalLayout_22 = new QHBoxLayout(widget_7);
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_53 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_53);

        label_logo_6 = new QLabel(widget_7);
        label_logo_6->setObjectName(QString::fromUtf8("label_logo_6"));
        label_logo_6->setEnabled(false);
        label_logo_6->setMinimumSize(QSize(103, 14));
        label_logo_6->setMaximumSize(QSize(103, 14));
        label_logo_6->setPixmap(QPixmap(QString::fromUtf8(":/logo/minilogo@2x.png")));
        label_logo_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_22->addWidget(label_logo_6);

        horizontalSpacer_54 = new QSpacerItem(234, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_54);


        horizontalLayout_24->addWidget(widget_7);

        widgetUP_2 = new QWidget(widget_5);
        widgetUP_2->setObjectName(QString::fromUtf8("widgetUP_2"));
        widgetUP_2->setMinimumSize(QSize(200, 0));
        horizontalLayout_23 = new QHBoxLayout(widgetUP_2);
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(widgetUP_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(118, 20));
        label_10->setStyleSheet(QString::fromUtf8("width: 118px;\n"
"height: 20px;\n"
"font-size: 16px;\n"
"font-family: PingFangSC-Semibold, PingFang SC;\n"
"font-weight: 600;\n"
"color: #000000;\n"
"line-height: 20px;"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(label_10);


        horizontalLayout_24->addWidget(widgetUP_2);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setMinimumSize(QSize(390, 32));
        widget_6->setMaximumSize(QSize(390, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget_6);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_46 = new QSpacerItem(14, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_46);

        pushButtonBuy_6 = new QPushButton(widget_6);
        pushButtonBuy_6->setObjectName(QString::fromUtf8("pushButtonBuy_6"));
        pushButtonBuy_6->setMinimumSize(QSize(104, 32));
        pushButtonBuy_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 226, 102);\n"
"width: 55px;\n"
"height: 20px;\n"
"font-size: 14px;\n"
"font-family: Tahoma;\n"
"color: #16314F;\n"
"line-height: 20px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/photo/buy@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonBuy_6->setIcon(icon);

        horizontalLayout_3->addWidget(pushButtonBuy_6);

        horizontalSpacer_47 = new QSpacerItem(18, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_47);

        pushButtonAccount_6 = new QPushButton(widget_6);
        pushButtonAccount_6->setObjectName(QString::fromUtf8("pushButtonAccount_6"));
        pushButtonAccount_6->setMinimumSize(QSize(30, 30));
        pushButtonAccount_6->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pushButtonAccount_6);

        horizontalSpacer_48 = new QSpacerItem(8, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_48);

        pushButtonPhone_6 = new QPushButton(widget_6);
        pushButtonPhone_6->setObjectName(QString::fromUtf8("pushButtonPhone_6"));
        pushButtonPhone_6->setMinimumSize(QSize(30, 30));
        pushButtonPhone_6->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("emblem-photos");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/photo/phone@2x.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        pushButtonPhone_6->setIcon(icon1);
        pushButtonPhone_6->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pushButtonPhone_6);

        horizontalSpacer_49 = new QSpacerItem(8, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_49);

        pushButtonSetting_6 = new QPushButton(widget_6);
        pushButtonSetting_6->setObjectName(QString::fromUtf8("pushButtonSetting_6"));
        pushButtonSetting_6->setMinimumSize(QSize(30, 30));
        pushButtonSetting_6->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pushButtonSetting_6);

        horizontalSpacer_50 = new QSpacerItem(14, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_50);

        widget = new QWidget(widget_6);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(1, 20));
        widget->setMaximumSize(QSize(1, 20));
        QFont font;
        font.setPointSize(1);
        widget->setFont(font);

        horizontalLayout_3->addWidget(widget);

        horizontalSpacer = new QSpacerItem(14, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonClose_11 = new QPushButton(widget_6);
        pushButtonClose_11->setObjectName(QString::fromUtf8("pushButtonClose_11"));
        pushButtonClose_11->setMinimumSize(QSize(30, 30));
        pushButtonClose_11->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pushButtonClose_11);

        horizontalSpacer_51 = new QSpacerItem(8, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_51);

        pushButtonClose_12 = new QPushButton(widget_6);
        pushButtonClose_12->setObjectName(QString::fromUtf8("pushButtonClose_12"));
        pushButtonClose_12->setEnabled(false);
        pushButtonClose_12->setMinimumSize(QSize(30, 30));
        pushButtonClose_12->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pushButtonClose_12);

        horizontalSpacer_52 = new QSpacerItem(14, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_52);


        horizontalLayout_24->addWidget(widget_6);


        verticalLayout_2->addWidget(widget_5);

        widget_8 = new QWidget(centralwidget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setMinimumSize(QSize(1024, 26));
        verticalLayout_3 = new QVBoxLayout(widget_8);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_12 = new QWidget(widget_8);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        horizontalLayout = new QHBoxLayout(widget_12);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(42, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        widget_2 = new QWidget(widget_12);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(300, 200));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 150, 80, 24));

        horizontalLayout->addWidget(widget_2);

        horizontalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_9 = new QWidget(widget_12);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setMinimumSize(QSize(300, 200));

        horizontalLayout->addWidget(widget_9);

        horizontalSpacer_4 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        widget_11 = new QWidget(widget_12);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        widget_11->setMinimumSize(QSize(300, 200));

        horizontalLayout->addWidget(widget_11);

        horizontalSpacer_5 = new QSpacerItem(42, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_3->addWidget(widget_12);

        widget_13 = new QWidget(widget_8);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        horizontalLayout_2 = new QHBoxLayout(widget_13);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(42, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        widget_10 = new QWidget(widget_13);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setMinimumSize(QSize(300, 200));

        horizontalLayout_2->addWidget(widget_10);

        horizontalSpacer_7 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        widget_14 = new QWidget(widget_13);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        widget_14->setMinimumSize(QSize(300, 200));

        horizontalLayout_2->addWidget(widget_14);

        horizontalSpacer_8 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        widget_15 = new QWidget(widget_13);
        widget_15->setObjectName(QString::fromUtf8("widget_15"));
        widget_15->setMinimumSize(QSize(300, 200));

        horizontalLayout_2->addWidget(widget_15);

        horizontalSpacer_9 = new QSpacerItem(42, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);


        verticalLayout_3->addWidget(widget_13);


        verticalLayout_2->addWidget(widget_8);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked(bool)), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_logo_6->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Screen Unlock", nullptr));
        pushButtonBuy_6->setText(QCoreApplication::translate("MainWindow", " Buy Now", nullptr));
        pushButtonAccount_6->setText(QCoreApplication::translate("MainWindow", "Account", nullptr));
        pushButtonPhone_6->setText(QString());
        pushButtonSetting_6->setText(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        pushButtonClose_11->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        pushButtonClose_12->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
