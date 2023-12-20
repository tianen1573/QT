#include "MainWindowImpl_win.h"

#ifdef Q_OS_WIN
#include "qt_windows.h"
#include "windowsx.h"
#include "uxtheme.h"
#include "dwmapi.h"
#include "WindowsAPIUtil.h"
#endif
#include <QLayout>
#include <QProcess>
#include <QScreen>
#include <QDebug>
#include <QEvent>
#include <QCoreApplication>
#include <QApplication>

static int BORDERWIDTH = 6;

MainWindowImpl_win::MainWindowImpl_win(QWidget *parent):
    QMainWindow(parent){
//    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
//    // Windows禁止系统休眠
//    ::SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);

    this->m_width = this->width();
    this->m_height = this->height();
    this->m_fixedWidth = 0;
    this->m_fixedHeight = 0;
    this->m_captionHeight = 48;
    this->m_isScale = false;

    BORDERWIDTH = BORDERWIDTH * window()->devicePixelRatio();
}

void MainWindowImpl_win::generalMinimize()
{
    QMainWindow::showMinimized();
}

void MainWindowImpl_win::applyTheme()
{
    this->m_width = this->width();
    this->m_height = this->height();

//    // aero 特效开启
//    HWND hWnd = (HWND)this->effectiveWinId();
//    if (WindowsAPIUtil::isCompositionEnalbe()) {
//        // 启动 caption
//        UINT style = GetWindowLong(hWnd,GWL_STYLE);
//        style &= ~WS_OVERLAPPEDWINDOW;
//        style |= WS_CAPTION;
//        SetWindowLong(hWnd,GWL_STYLE,style);
//        // 设置边距开启阴影
//        MARGINS margins = {1,1,1,1};
//        HRESULT hr = DwmExtendFrameIntoClientArea(hWnd, &margins);
//        SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
//        if (this->centralWidget()) {
//            if(this->m_fixedWidth && this->m_fixedHeight) {
//                this->resize(this->m_fixedWidth, this->m_fixedHeight);
//            } else {
//                this->resize(this->m_width, this->m_height);
////                this->resize(this->width(), this->height());
//            }
//            this->centralWidget()->layout()->setMargin(0);
//            this->centralWidget()->setStyleSheet("QWidget#centralwidget{border: 0px;}");
//        }
//    } else {
//        // 关闭caption
//        UINT style = GetWindowLong(hWnd,GWL_STYLE);
//        style &= ~WS_CAPTION;
//        SetWindowLong(hWnd,GWL_STYLE,style);
//        // 保留1px边框
//        MARGINS margins = {1,1,1,1};
//        HRESULT hr = DwmExtendFrameIntoClientArea(hWnd, &margins);
//        SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
//        if (this->centralWidget()) {
//            if(this->m_fixedWidth && this->m_fixedHeight) {
//                this->resize(this->m_fixedWidth + 2, this->m_fixedHeight + 2);
//            } else {
//                this->resize(this->m_width, this->m_height);
////                this->resize(this->width(), this->height());
//            }
//            this->centralWidget()->setStyleSheet("QWidget#centralwidget{border: 1px solid #111121;}");
//            if (this->centralWidget()->layout()) {
//                this->centralWidget()->layout()->setMargin(1);
//            }
//        }
//    }
}


bool MainWindowImpl_win::titleButtonAreaJudge(QPoint pos)
{
    if ( getRealRect(QRect(980, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(942, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(884, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(846, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(808, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(770, 9, 30, 30)).contains(pos) ||
         getRealRect(QRect(12, 15, 83, 25)).contains(pos) ||
         getRealRect(QRect(685, 15, 104, 32)).contains(pos)) {
        return true;
    }
    else {
        return false;
    }
}

bool MainWindowImpl_win::handleBorderHit(int lparamx, int lparamy, int left, int right, int top, int bottom, long borderW, long* result)
{
    // 八个方位选择
    if(this->m_isScale) {
        const LONG borderWidth = 8 * borderW; //This value can be arbitrarily large as only intentionally-HTTRANSPARENT'd messages arrive here

        //bottom left corner
        if (lparamx >= left && lparamx < left + borderWidth &&
            lparamy < bottom && lparamy >= bottom - borderWidth)
        {
            qDebug() << "bottom left";
            *result = HTBOTTOMLEFT;
            return true;
        }
        //bottom right corner
        if (lparamx < right && lparamx >= right - borderWidth &&
            lparamy < bottom && lparamy >= bottom - borderWidth)
        {
            qDebug() << "bottom right";
            *result = HTBOTTOMRIGHT;
            return true;
        }
        //top left corner
        if (lparamx >= left && lparamx < left + borderWidth &&
            lparamy >= top && lparamy < top + borderWidth)
        {
            qDebug() << "top left";
            *result = HTTOPLEFT;
            return true;
        }
        //top right corner
        if (lparamx < right && lparamx >= right - borderWidth &&
            lparamy >= top && lparamy < top + borderWidth)
        {
            qDebug() << "top right";
            *result = HTTOPRIGHT;
            return true;
        }
        //left border
        if (lparamx >= left && lparamx < left + borderWidth)
        {
//                qDebug() << "left";
//                *result = HTLEFT;
//                return true;
        }
        //right border
        if (lparamx < right && lparamx >= right - borderWidth)
        {
//                qDebug() << "right";
//                *result = HTRIGHT;
//                return true;
        }
        //bottom border
        if (lparamy < bottom && lparamy >= bottom - borderWidth)
        {
//                qDebug() << "bottom";
//                *result = HTBOTTOM;
//                return true;
        }
        //top border
        if (lparamy >= top && lparamy < top + borderWidth)
        {
//                qDebug() << "top";
//                *result = HTTOP;
//                return true;
        }
    }

    return false; // false代表不处理
}

QRect MainWindowImpl_win::getRealRect(const QRect &rect)
{
////    QRect result;
//    QRect result = rect;
//#ifdef Q_OS_WIN
//    int dpi = WindowsAPIUtil::GetWindowDPI(reinterpret_cast<HWND>(effectiveWinId()));
//    double rate =  dpi / 96.0;
////    double rate =  dpi;
//    result.setLeft(rect.x() * rate);
//    result.setTop(rect.y() * rate);
//    result.setWidth(rect.width() * rate);
//    result.setHeight(rect.height() * rate);
//#endif
//    return result;
}

bool MainWindowImpl_win::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Q_OS_WIN
    MSG* msg = (MSG*)message;
    switch (msg->message) {

    case WM_NCHITTEST:
    {
        //
        HWND hwnd = reinterpret_cast<HWND>(effectiveWinId());
//        int dpi = WindowsAPIUtil::GetWindowDPI(hwnd);
        RECT winrect;
        GetWindowRect(hwnd, &winrect);
        int lparamx = GET_X_LPARAM(msg->lParam);
        int lparamy = GET_Y_LPARAM(msg->lParam);
        int xPos = lparamx - winrect.left;
        int yPos = lparamy - winrect.top;
//        int captionHeight = m_captionHeight * (dpi / 96.0);
////        int captionHeight = m_captionHeight * (dpi);
//        if (yPos >= 0 && yPos <= captionHeight && !titleButtonAreaJudge(QPoint(xPos, yPos))) {
//            *result = HTCAPTION; // HTCAPTION 判定，窗口顶部实现拖放
//            return true;
//        }

        // 八个方位, 返回true，代表已经处理过了, 否则交给后面处理
        // int lparamx, int lparamy, int left, int right, int top, int bottom, long borderW, long* result
        const LONG borderW = 1 * window()->devicePixelRatio();
        if(handleBorderHit(lparamx, lparamy, winrect.left, winrect.right, winrect.top, winrect.bottom, borderW, result)){
            return true;
        }
    }
        break;
    case WM_NCLBUTTONDBLCLK:
        return true;
    case WM_ACTIVATE:{
        applyTheme();
        break;
    }
    case WM_PAINT: {
        applyTheme();
        emit paint();
        break;
    }
    case WM_NCCALCSIZE:
    {
//        //this kills the window frame and title bar we added with
//        //WS_THICKFRAME and WS_CAPTION
//        if (msg->wParam == TRUE && WindowsAPIUtil::isCompositionEnalbe())  {
//            LPNCCALCSIZE_PARAMS params = (LPNCCALCSIZE_PARAMS)msg->lParam;
//            params->rgrc[2] = params->rgrc[0];
//            params->rgrc[0] = params->rgrc[1];
//            *result = WVR_ALIGNTOP | WVR_ALIGNLEFT | WVR_REDRAW ;
//            return true;
//        }
        break;
    }
    case 0x031E/*WM_DWMCOMPOSITIONCHANGED*/:
    {
        applyTheme();
        break;
    }
//        return DefWindowProc(hWnd, message, wParam, lParam);
    }
#endif
    return QMainWindow::nativeEvent(eventType, message, result);
}


void MainWindowImpl_win::changeEvent(QEvent * e)
{
    if (e->type() == QEvent::Show)
    {
        applyTheme();
    }
    QWidget::changeEvent(e);
}

void MainWindowImpl_win::setFixedSize(int width, int height)
{
    this->m_fixedHeight = height;
    this->m_fixedWidth = width;
}

void MainWindowImpl_win::setCaptionHeight(int newCaptionHeight)
{
    m_captionHeight = newCaptionHeight;
}

void MainWindowImpl_win::enableScale(bool scale)
{
    this->m_isScale = scale;
}
