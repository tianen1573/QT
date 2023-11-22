#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QListView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model.appendRow(new QStandardItem("Short message."));
    model.appendRow(new QStandardItem("This is a longer message that requires more height."));
    model.appendRow(new QStandardItem("Another message."));
    model.appendRow(new QStandardItem("A very long message that needs even more height than before."));

    QStringList sl;
    sl << "asdadasda" << "sada" << "sadogfhnreojqf" << "sadasdgrhytsvbyjurfdv";
    int row = model_sl.rowCount(); // 获取当前行数
    model_sl.insertRows(row, sl.count()); // 插入新行
    for (int i = 0; i < sl.count(); ++i) {
        QModelIndex index = model_sl.index(row + i); // 获取插入行的索引
        model_sl.setData(index, sl[i], Qt::DisplayRole); // 设置数据
    }
    ui->listView->setModel(&model_sl);

    ui->listView->setItemDelegate(&delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

