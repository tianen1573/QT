/********************************************************************************
** Form generated from reading UI file 'FloatingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOATINGWINDOW_H
#define UI_FLOATINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FloatingWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_back;
    QPushButton *btn_full;
    QPushButton *btn_C;
    QPushButton *btn_A;
    QPushButton *btn_B;

    void setupUi(QWidget *FloatingWindow)
    {
        if (FloatingWindow->objectName().isEmpty())
            FloatingWindow->setObjectName(QString::fromUtf8("FloatingWindow"));
        FloatingWindow->resize(360, 90);
        FloatingWindow->setMinimumSize(QSize(330, 90));
        FloatingWindow->setMaximumSize(QSize(360, 90));
        FloatingWindow->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        horizontalLayout = new QHBoxLayout(FloatingWindow);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(30, 30, 30, 30);
        btn_back = new QPushButton(FloatingWindow);
        btn_back->setObjectName(QString::fromUtf8("btn_back"));

        horizontalLayout->addWidget(btn_back);

        btn_full = new QPushButton(FloatingWindow);
        btn_full->setObjectName(QString::fromUtf8("btn_full"));

        horizontalLayout->addWidget(btn_full);

        btn_C = new QPushButton(FloatingWindow);
        btn_C->setObjectName(QString::fromUtf8("btn_C"));

        horizontalLayout->addWidget(btn_C);

        btn_A = new QPushButton(FloatingWindow);
        btn_A->setObjectName(QString::fromUtf8("btn_A"));

        horizontalLayout->addWidget(btn_A);

        btn_B = new QPushButton(FloatingWindow);
        btn_B->setObjectName(QString::fromUtf8("btn_B"));

        horizontalLayout->addWidget(btn_B);


        retranslateUi(FloatingWindow);

        QMetaObject::connectSlotsByName(FloatingWindow);
    } // setupUi

    void retranslateUi(QWidget *FloatingWindow)
    {
        FloatingWindow->setWindowTitle(QCoreApplication::translate("FloatingWindow", "Form", nullptr));
#if QT_CONFIG(tooltip)
        btn_back->setToolTip(QCoreApplication::translate("FloatingWindow", "Back", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_back->setText(QString());
#if QT_CONFIG(tooltip)
        btn_full->setToolTip(QCoreApplication::translate("FloatingWindow", "NoFull", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_full->setText(QCoreApplication::translate("FloatingWindow", "Full", nullptr));
        btn_C->setText(QCoreApplication::translate("FloatingWindow", "PushButton", nullptr));
        btn_A->setText(QCoreApplication::translate("FloatingWindow", "PushButton", nullptr));
        btn_B->setText(QCoreApplication::translate("FloatingWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FloatingWindow: public Ui_FloatingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOATINGWINDOW_H
