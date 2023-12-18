/********************************************************************************
** Form generated from reading UI file 'WidgetTestCenter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETTESTCENTER_H
#define UI_WIDGETTESTCENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetTestCenter
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QTextEdit *textEdit_2;
    QPushButton *pushButton_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QTextEdit *textEdit_3;
    QPushButton *pushButton_3;
    QLabel *label;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *WidgetTestCenter)
    {
        if (WidgetTestCenter->objectName().isEmpty())
            WidgetTestCenter->setObjectName(QString::fromUtf8("WidgetTestCenter"));
        WidgetTestCenter->resize(648, 600);
        WidgetTestCenter->setMinimumSize(QSize(400, 600));
        WidgetTestCenter->setMaximumSize(QSize(16777215, 16777215));
        WidgetTestCenter->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        horizontalLayout = new QHBoxLayout(WidgetTestCenter);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget = new QWidget(WidgetTestCenter);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_2->addWidget(label_2);

        textEdit = new QTextEdit(widget_4);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(0, 40));
        textEdit->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_2->addWidget(textEdit);

        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 40));
        label_3->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_3->addWidget(label_3);

        textEdit_2 = new QTextEdit(widget_5);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setMinimumSize(QSize(0, 40));
        textEdit_2->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_3->addWidget(textEdit_2);

        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 40));
        label_4->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_4->addWidget(label_4);

        textEdit_3 = new QTextEdit(widget_6);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setMinimumSize(QSize(0, 40));
        textEdit_3->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_4->addWidget(textEdit_3);

        pushButton_3 = new QPushButton(widget_6);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);


        verticalLayout_2->addWidget(widget_6);


        verticalLayout->addWidget(widget_2);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_5 = new QHBoxLayout(widget_3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);

        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(WidgetTestCenter);

        QMetaObject::connectSlotsByName(WidgetTestCenter);
    } // setupUi

    void retranslateUi(QWidget *WidgetTestCenter)
    {
        WidgetTestCenter->setWindowTitle(QCoreApplication::translate("WidgetTestCenter", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("WidgetTestCenter", "PushButton", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WidgetTestCenter", "PushButton", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WidgetTestCenter", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetTestCenter", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetTestCenter: public Ui_WidgetTestCenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETTESTCENTER_H
