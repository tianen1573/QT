#include "MainWindow.h"
#include "ui_MainWindow.h"


#include <QDebug>
#include <QMessageBox>
#include "Sql.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); // 充满表格
    ui->tableWidget->verticalHeader()->setVisible(true); //设置行号列,true为显示
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    ui->tableWidget->horizontalHeader()->resizeSection(0, 50);
    ui->tableWidget->horizontalHeader()->resizeSection(1, 100);
    ui->tableWidget->horizontalHeader()->resizeSection(2, 200);

    Sql* p_sql = new Sql;

    connect(ui->pushButtonQuery, SIGNAL(clicked()), p_sql, SLOT(querySql()));
    connect(p_sql, &Sql::setWidgetItem, this, &MainWindow::onSetWidgetItem);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetWidgetItem(const QStringList &sl)
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    for(int i = 0; i < sl.length(); ++ i){
        ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(sl.at(i)));
    }

}

