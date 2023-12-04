/********************************************************************************
** Form generated from reading UI file 'WidgetHome.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETHOME_H
#define UI_WIDGETHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetHome
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *WidgetHome)
    {
        if (WidgetHome->objectName().isEmpty())
            WidgetHome->setObjectName(QString::fromUtf8("WidgetHome"));
        WidgetHome->resize(629, 486);
        label = new QLabel(WidgetHome);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 180, 351, 161));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        pushButton = new QPushButton(WidgetHome);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(480, 430, 80, 24));

        retranslateUi(WidgetHome);

        QMetaObject::connectSlotsByName(WidgetHome);
    } // setupUi

    void retranslateUi(QWidget *WidgetHome)
    {
        WidgetHome->setWindowTitle(QCoreApplication::translate("WidgetHome", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetHome", "Hello", nullptr));
        pushButton->setText(QCoreApplication::translate("WidgetHome", "\347\231\273\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetHome: public Ui_WidgetHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETHOME_H
