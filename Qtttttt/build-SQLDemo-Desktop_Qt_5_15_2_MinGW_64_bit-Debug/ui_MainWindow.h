/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonQuery;
    QPushButton *pushButtonModify;
    QPushButton *pushButtonInsert;
    QPushButton *pushButtonDelete;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextEdit *textEditID;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEditNAME;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTextEdit *textEditPWD;
    QWidget *widget_6;
    QVBoxLayouttextEditBIRLayout_4;
    QLabel *label_4;
    QTextEdit *textEdit_4;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1115, 597);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonQuery = new QPushButton(widget);
        pushButtonQuery->setObjectName(QString::fromUtf8("pushButtonQuery"));

        horizontalLayout->addWidget(pushButtonQuery);

        pushButtonModify = new QPushButton(widget);
        pushButtonModify->setObjectName(QString::fromUtf8("pushButtonModify"));

        horizontalLayout->addWidget(pushButtonModify);

        pushButtonInsert = new QPushButton(widget);
        pushButtonInsert->setObjectName(QString::fromUtf8("pushButtonInsert"));

        horizontalLayout->addWidget(pushButtonInsert);

        pushButtonDelete = new QPushButton(widget);
        pushButtonDelete->setObjectName(QString::fromUtf8("pushButtonDelete"));

        horizontalLayout->addWidget(pushButtonDelete);


        verticalLayout_5->addWidget(widget);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 50));
        widget_3->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 50));
        widget_4->setMaximumSize(QSize(16777215, 70));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, -1, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        verticalLayout_2->addWidget(label_2);

        textEditID = new QTextEdit(widget_4);
        textEditID->setObjectName(QString::fromUtf8("textEditID"));
        textEditID->setMinimumSize(QSize(0, 50));
        textEditID->setMaximumSize(QSize(16777215, 50));

        verticalLayout_2->addWidget(textEditID);


        horizontalLayout_2->addWidget(widget_4);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 50));
        widget_2->setMaximumSize(QSize(16777215, 70));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, -1, 0);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 20));
        label->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(label);

        textEditNAME = new QTextEdit(widget_2);
        textEditNAME->setObjectName(QString::fromUtf8("textEditNAME"));
        textEditNAME->setMinimumSize(QSize(0, 50));
        textEditNAME->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(textEditNAME);


        horizontalLayout_2->addWidget(widget_2);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(0, 50));
        widget_5->setMaximumSize(QSize(16777215, 70));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, -1, 0);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        verticalLayout_3->addWidget(label_3);

        textEditPWD = new QTextEdit(widget_5);
        textEditPWD->setObjectName(QString::fromUtf8("textEditPWD"));
        textEditPWD->setMinimumSize(QSize(0, 50));
        textEditPWD->setMaximumSize(QSize(16777215, 50));

        verticalLayout_3->addWidget(textEditPWD);


        horizontalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setMinimumSize(QSize(0, 50));
        widget_6->setMaximumSize(QSize(16777215, 70));
        verticalLayout_4 = new QVBoxLayout(widget_6);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, -1, 0);
        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 20));
        label_4->setMaximumSize(QSize(16777215, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        textEditBIRyout_4->addWidget(label_4);

       tetextEditBIR = new QTextEdit(widget_6);
        textEditBIR->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setMinimumSize(QSize(0, 50));
        textEdit_4->setMaximumSize(QtextEditBIR215, 50));

        verticalLayout_4->addWidget(textEdit_4);


        horizontalLayout_2->addWidget(widget_6);


        verticalLayout_5->addWidget(widget_3);

        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_5->addWidget(tableWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonQuery->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        pushButtonModify->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        pushButtonInsert->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "NAME", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PWD", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "BIR: yyyy-mm-dd", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "PWD", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "BIR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
