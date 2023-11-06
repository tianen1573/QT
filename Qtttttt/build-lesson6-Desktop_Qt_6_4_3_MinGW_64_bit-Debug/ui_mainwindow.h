/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_3;
    QLabel *label_6;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(820, 483);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(0, 101));
        widget_3->setMaximumSize(QSize(16777215, 101));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(303, 50));
        widget->setMaximumSize(QSize(16777215, 50));
        widget->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(lineEdit_2);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(303, 50));
        widget_2->setMaximumSize(QSize(16777215, 50));
        widget_2->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(pushButton);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_4 = new QLineEdit(widget_2);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setMinimumSize(QSize(100, 50));

        horizontalLayout_2->addWidget(lineEdit_4);


        verticalLayout->addWidget(widget_2);


        verticalLayout_2->addWidget(widget_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(502, 151));
        widget_4->setMaximumSize(QSize(16777215, 152));
        widget_4->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        gridLayout = new QGridLayout(widget_4);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(100, 50));
        label_3->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(widget_4);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setMinimumSize(QSize(200, 50));
        lineEdit_3->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(lineEdit_3, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(200, 50));
        pushButton_2->setMaximumSize(QSize(200, 50));

        gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

        label_5 = new QLabel(widget_4);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(100, 50));
        label_5->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        lineEdit_5 = new QLineEdit(widget_4);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setMinimumSize(QSize(200, 50));
        lineEdit_5->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(lineEdit_5, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(200, 50));
        pushButton_3->setMaximumSize(QSize(200, 50));

        gridLayout->addWidget(pushButton_3, 1, 2, 1, 1);

        label_6 = new QLabel(widget_4);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(100, 50));
        label_6->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        lineEdit_6 = new QLineEdit(widget_4);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setMinimumSize(QSize(200, 50));
        lineEdit_6->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(lineEdit_6, 2, 1, 1, 1);

        pushButton_4 = new QPushButton(widget_4);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(200, 50));
        pushButton_4->setMaximumSize(QSize(200, 50));

        gridLayout->addWidget(pushButton_4, 2, 2, 1, 1);


        verticalLayout_2->addWidget(widget_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\225\260 \351\207\217", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\215\225 \344\273\267", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "5.61", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\241 \347\256\227  ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\200\273 \344\273\267", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "67.32", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
