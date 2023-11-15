#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUpdateTxt(const QString& txt);
    void onUpdateBar(int p);
    void onDisplayWarningDialog(const QString& name, const QString& desc);
private:
    QTextEdit* textEdit;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
