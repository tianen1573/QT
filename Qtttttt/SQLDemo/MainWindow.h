#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void readTextEdit(const QStringList& sl);
private:
    Ui::MainWindow *ui;
signals:
    void querySql(const QStringList & sl);
    void deleteSql(const QStringList & sl);
    void modifySql(const QStringList & sl);
    void insertSql(const QStringList & sl);
private slots:
    void onSetWidgetItem(const QStringList& sl);
    void onQuerySqlAndInitWidget();
    void onDeleteSql();
    void onModifySql();
    void onInsert();
};
#endif // MAINWINDOW_H
