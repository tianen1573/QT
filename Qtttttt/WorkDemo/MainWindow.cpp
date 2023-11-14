#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "WorkHome.h"
#include "WorkLogin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_workLogin = new WorkLogin(ui->stackedWidget);
    m_workHome = new WorkHome(ui->stackedWidget);

    connect(m_workLogin, &WorkLogin::back, this, &MainWindow::onLoginBack);
    connect(m_workLogin, &WorkLogin::next, this, &MainWindow::onLoginNext);

    connect(m_workHome, &WorkHome::back, this, &MainWindow::onHomeBack);
    connect(m_workHome, &WorkHome::next, this, &MainWindow::onHomeNext);

    m_workLogin->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginBack()
{

}

void MainWindow::onLoginNext()
{
    m_workHome->start();
}

void MainWindow::onHomeBack()
{
    m_workLogin->start();
}

void MainWindow::onHomeNext()
{

}

