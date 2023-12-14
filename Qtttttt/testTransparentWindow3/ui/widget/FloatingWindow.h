#ifndef FLOATINGWINDOW_H
#define FLOATINGWINDOW_H

#include <QWidget>

namespace Ui {
class FloatingWindow;
}

class FloatingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingWindow(QWidget *parent = nullptr);
    ~FloatingWindow();

signals:

    void checkFull();

private slots:

    void on_btn_full_clicked();

private:
    Ui::FloatingWindow *ui;
};

#endif // FLOATINGWINDOW_H
