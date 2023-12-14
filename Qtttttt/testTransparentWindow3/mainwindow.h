#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WidgetSettingMain;
class FloatingWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    // other
    WidgetSettingMain * m_mainSetting;
    FloatingWindow * m_floatingWindow;
    QTimer *timer;

    // 全屏
    bool m_isFullScreen;
    QSize m_size;

    // 拖拽窗口
    QPoint m_dragStartPosition; // 鼠标按下时的位置
    bool m_isDragging = false; // 拖动标志
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool m_resizing = false;
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_btn_full_clicked();
    void on_btn_max_clicked();
    void resetTimer();
    void hideWindow();
};
#endif // MAINWINDOW_H
