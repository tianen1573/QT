#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMouseEvent>

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
    Ui::MainWindow *ui;

    // 拖拽窗口
    QPoint m_dragStartPosition; // 鼠标按下时的位置
    bool m_isDragging = false; // 拖动标志
protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            // 记录鼠标按下时的位置
            m_dragStartPosition = event->globalPos();
            // 设置拖动标志
            m_isDragging = true;
        }
        QMainWindow::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_isDragging) {
            // 计算鼠标移动的距离
            QPoint distance = event->globalPos() - m_dragStartPosition;
            // 更新主窗口的位置
            move(pos() + distance);
            // 更新鼠标按下的位置
            m_dragStartPosition = event->globalPos();
        }
        QMainWindow::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            // 清除拖动标志
            m_isDragging = false;
        }
        QMainWindow::mouseReleaseEvent(event);
    }
private slots:
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
};
#endif // MAINWINDOW_H
