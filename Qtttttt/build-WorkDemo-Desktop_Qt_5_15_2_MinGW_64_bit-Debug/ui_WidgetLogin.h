/********************************************************************************
** Form generated from reading UI file 'WidgetLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETLOGIN_H
#define UI_WIDGETLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetLogin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_account;
    QLineEdit *lineEdit_pwd;
    QPushButton *pushButton;
    QLabel *lab_err;

    void setupUi(QWidget *WidgetLogin)
    {
        if (WidgetLogin->objectName().isEmpty())
            WidgetLogin->setObjectName(QString::fromUtf8("WidgetLogin"));
        WidgetLogin->resize(819, 559);
        label = new QLabel(WidgetLogin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 190, 101, 51));
        label_2 = new QLabel(WidgetLogin);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 260, 101, 51));
        lineEdit_account = new QLineEdit(WidgetLogin);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));
        lineEdit_account->setGeometry(QRect(280, 200, 113, 23));
        lineEdit_pwd = new QLineEdit(WidgetLogin);
        lineEdit_pwd->setObjectName(QString::fromUtf8("lineEdit_pwd"));
        lineEdit_pwd->setGeometry(QRect(280, 270, 113, 23));
        pushButton = new QPushButton(WidgetLogin);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 380, 80, 24));
        lab_err = new QLabel(WidgetLogin);
        lab_err->setObjectName(QString::fromUtf8("lab_err"));
        lab_err->setGeometry(QRect(190, 340, 211, 16));

        retranslateUi(WidgetLogin);

        QMetaObject::connectSlotsByName(WidgetLogin);
    } // setupUi

    void retranslateUi(QWidget *WidgetLogin)
    {
        WidgetLogin->setWindowTitle(QCoreApplication::translate("WidgetLogin", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetLogin", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetLogin", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("WidgetLogin", "\347\231\273\345\275\225", nullptr));
        lab_err->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetLogin: public Ui_WidgetLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETLOGIN_H
