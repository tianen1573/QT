#ifndef MAINWINDOWIMPL_WIN_H
#define MAINWINDOWIMPL_WIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include "CommonGlobal.h"

// 无边框窗口 win 和 mac 实现
class MainWindowImpl_win : public QMainWindow
{
    Q_OBJECT
public:

    explicit MainWindowImpl_win(QWidget *parent);
public slots:
    void generalMinimize();

protected:
    void applyTheme();
    // 判断鼠标是否在标题栏点击
    virtual bool titleButtonAreaJudge(QPoint pos);
    // 自定义边框
    virtual bool handleBorderHit(int lparamx, int lparamy, int left, int right, int top, int bottom, long borderW, long* result);
    QRect getRealRect(const QRect &rect);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    void changeEvent(QEvent *);

    void setFixedSize(int width, int height);

    void setCaptionHeight(int newCaptionHeight);

    ///
    /// \brief 是否可以缩放
    /// \param scale
    ///
    void enableScale(bool scale);
signals:
    void paint();

protected:
    int m_width;
    int m_height;
    int m_captionHeight;
    int m_fixedWidth;
    int m_fixedHeight;
    bool m_isScale;
};

#endif // MAINWINDOWIMPL_WIN_H
