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
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widgetBody;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetHeader;
    QHBoxLayout *horizontalLayout_11;
    QLabel *lab_title;
    QPushButton *btn_max;
    QPushButton *btn_full;
    QPushButton *btn_close;
    QStackedWidget *stackedMainWidget;
    QWidget *widgetMenu;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widgetNav;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btn_setting;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(482, 682);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widgetBody = new QWidget(centralwidget);
        widgetBody->setObjectName(QString::fromUtf8("widgetBody"));
        widgetBody->setMinimumSize(QSize(400, 680));
        widgetBody->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widgetBody);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetHeader = new QWidget(widgetBody);
        widgetHeader->setObjectName(QString::fromUtf8("widgetHeader"));
        widgetHeader->setMinimumSize(QSize(400, 80));
        widgetHeader->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid red;"));
        horizontalLayout_11 = new QHBoxLayout(widgetHeader);
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        lab_title = new QLabel(widgetHeader);
        lab_title->setObjectName(QString::fromUtf8("lab_title"));

        horizontalLayout_11->addWidget(lab_title);

        btn_max = new QPushButton(widgetHeader);
        btn_max->setObjectName(QString::fromUtf8("btn_max"));

        horizontalLayout_11->addWidget(btn_max);

        btn_full = new QPushButton(widgetHeader);
        btn_full->setObjectName(QString::fromUtf8("btn_full"));

        horizontalLayout_11->addWidget(btn_full);

        btn_close = new QPushButton(widgetHeader);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));

        horizontalLayout_11->addWidget(btn_close);


        verticalLayout_2->addWidget(widgetHeader);

        stackedMainWidget = new QStackedWidget(widgetBody);
        stackedMainWidget->setObjectName(QString::fromUtf8("stackedMainWidget"));
        stackedMainWidget->setMinimumSize(QSize(400, 600));
        stackedMainWidget->setStyleSheet(QString::fromUtf8(""));
        stackedMainWidget->setLineWidth(0);

        verticalLayout_2->addWidget(stackedMainWidget);


        horizontalLayout->addWidget(widgetBody);

        widgetMenu = new QWidget(centralwidget);
        widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
        widgetMenu->setMinimumSize(QSize(80, 300));
        verticalLayout = new QVBoxLayout(widgetMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 56, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widgetNav = new QWidget(widgetMenu);
        widgetNav->setObjectName(QString::fromUtf8("widgetNav"));
        widgetNav->setMinimumSize(QSize(80, 300));
        widgetNav->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(widgetNav);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        btn_setting = new QPushButton(widgetNav);
        btn_setting->setObjectName(QString::fromUtf8("btn_setting"));
        btn_setting->setMinimumSize(QSize(60, 60));
        btn_setting->setMaximumSize(QSize(60, 60));

        verticalLayout_3->addWidget(btn_setting);


        verticalLayout->addWidget(widgetNav);

        verticalSpacer_2 = new QSpacerItem(20, 56, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(widgetMenu);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(btn_close, SIGNAL(clicked()), MainWindow, SLOT(close()));

        stackedMainWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lab_title->setText(QCoreApplication::translate("MainWindow", "TEST_TIGER", nullptr));
        btn_max->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        btn_full->setText(QCoreApplication::translate("MainWindow", "FULL", nullptr));
        btn_close->setText(QCoreApplication::translate("MainWindow", "CLose", nullptr));
        btn_setting->setText(QCoreApplication::translate("MainWindow", "setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
