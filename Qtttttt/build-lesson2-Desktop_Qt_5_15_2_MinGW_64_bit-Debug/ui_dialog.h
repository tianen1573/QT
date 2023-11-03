/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxUnderline;
    QCheckBox *checkBoxItalic;
    QCheckBox *checkBoxBold;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonBlue;
    QRadioButton *radioButtonRed;
    QRadioButton *radioButtonBlack;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxUnderline = new QCheckBox(groupBox);
        checkBoxUnderline->setObjectName(QString::fromUtf8("checkBoxUnderline"));

        horizontalLayout->addWidget(checkBoxUnderline);

        checkBoxItalic = new QCheckBox(groupBox);
        checkBoxItalic->setObjectName(QString::fromUtf8("checkBoxItalic"));

        horizontalLayout->addWidget(checkBoxItalic);

        checkBoxBold = new QCheckBox(groupBox);
        checkBoxBold->setObjectName(QString::fromUtf8("checkBoxBold"));

        horizontalLayout->addWidget(checkBoxBold);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButtonBlue = new QRadioButton(groupBox_2);
        radioButtonBlue->setObjectName(QString::fromUtf8("radioButtonBlue"));

        horizontalLayout_2->addWidget(radioButtonBlue);

        radioButtonRed = new QRadioButton(groupBox_2);
        radioButtonRed->setObjectName(QString::fromUtf8("radioButtonRed"));

        horizontalLayout_2->addWidget(radioButtonRed);

        radioButtonBlack = new QRadioButton(groupBox_2);
        radioButtonBlack->setObjectName(QString::fromUtf8("radioButtonBlack"));

        horizontalLayout_2->addWidget(radioButtonBlack);


        verticalLayout->addWidget(groupBox_2);

        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QFont font;
        font.setPointSize(24);
        plainTextEdit->setFont(font);

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonOK = new QPushButton(Dialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        horizontalLayout_3->addWidget(pushButtonOK);

        pushButtonCancel = new QPushButton(Dialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_3->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(68, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(Dialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        horizontalLayout_3->addWidget(pushButtonClose);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(pushButtonCancel, SIGNAL(clicked()), Dialog, SLOT(reject()));
        QObject::connect(pushButtonClose, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "GroupBox", nullptr));
        checkBoxUnderline->setText(QCoreApplication::translate("Dialog", "Underline", nullptr));
        checkBoxItalic->setText(QCoreApplication::translate("Dialog", "Italic", nullptr));
        checkBoxBold->setText(QCoreApplication::translate("Dialog", "Bold", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "GroupBox", nullptr));
        radioButtonBlue->setText(QCoreApplication::translate("Dialog", "Blue", nullptr));
        radioButtonRed->setText(QCoreApplication::translate("Dialog", "Red", nullptr));
        radioButtonBlack->setText(QCoreApplication::translate("Dialog", "Black", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("Dialog", "Helloc QT!\n"
"This is YiXuan.", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("Dialog", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("Dialog", "\345\217\226\346\266\210", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
