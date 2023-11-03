#include "dialog.h"
#include <QHBoxLayout> // 水平布局
#include <QVBoxLayout> // 垂直布局

void Dialog::InitUI()
{
    checkBoxUnderline = new QCheckBox(tr("Underline"));
    checkBoxItalic = new QCheckBox(tr("Italic"));
    checkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLayout1 = new QHBoxLayout;
    HLayout1->addWidget(checkBoxUnderline);
    HLayout1->addWidget(checkBoxItalic);
    HLayout1->addWidget(checkBoxBold);

    //    setLayout(HLayout1);

    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    rBtnRed = new QRadioButton(tr("Red"));
    QHBoxLayout *HLayout2 = new QHBoxLayout;
    HLayout2->addWidget(rBtnBlack);
    HLayout2->addWidget(rBtnBlue);
    HLayout2->addWidget(rBtnRed);

    plainTextEdit = new QPlainTextEdit();
    QFont font = plainTextEdit->font();
    font.setPointSize(20);
    plainTextEdit->setFont(font);
    plainTextEdit->setPlainText("Hello Qt!\n\nThis is YiXuan.");

    btnOK = new QPushButton(tr("OK"));
    btnClose = new QPushButton(tr("Close"));
    btnCancel = new QPushButton(tr("Cancel"));
    QHBoxLayout *HLayout3 = new QHBoxLayout;
    HLayout3->addStretch();
    HLayout3->addWidget(btnOK);
    HLayout3->addWidget(btnClose);
    HLayout3->addStretch();
    HLayout3->addWidget(btnCancel);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addLayout(HLayout1);
    VLayout->addLayout(HLayout2);
    VLayout->addWidget(plainTextEdit);
    VLayout->addLayout(HLayout3);
    setLayout(VLayout);

}

void Dialog::InitSignalSlots()
{
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));

    connect(checkBoxUnderline, SIGNAL(clicked(bool)), this, SLOT(on_checkUnderline(bool)));
    connect(checkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_checkItalic(bool)));
    connect(checkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_checkBold(bool)));

    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

void Dialog::on_checkUnderline(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setUnderline(checked);
    plainTextEdit->setFont(font);
}
void Dialog::on_checkItalic(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setItalic(checked);
    plainTextEdit->setFont(font);
}
void Dialog::on_checkBold(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setBold(checked);
    plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet = plainTextEdit->palette();

    if(rBtnBlack->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    else if(rBtnRed->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::red);
    }
    else if(rBtnBlue->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::blue);
    }
    else
    {
        plet.setColor(QPalette::Text, Qt::black);
    }

    plainTextEdit->setPalette(plet);

}


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    InitUI();
    InitSignalSlots();
}

Dialog::~Dialog()
{
}

