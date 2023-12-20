#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QRect>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <GlobalReferences.h>
#include <QGraphicsDropShadowEffect>
#include <QtMath>
#include <QtCore>
#include <QScreen>

#include "ui/widget/WidgetSettingMain.h"
#include "ui/widget/FloatingWindow.h"
#include "ui/widget/WidgetTestCenter.h"

MainWindow::MainWindow(QWidget *parent)
    : MainWindowImpl_win(parent)
    , m_isFullScreen(false)
    , m_mainSetting(new WidgetSettingMain)
    , m_floatingWindow(new FloatingWindow)
    , m_testCenter(new WidgetTestCenter)
    , ui(new Ui::MainWindow)
{
    QApplication::instance()->installEventFilter(this);

    // 透明+无边框
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->setMouseTracking(true);
//    this->ui->stackedMainWidget->setMouseTracking(true);

    connect(m_floatingWindow, &FloatingWindow::checkFull, this, &MainWindow::on_btn_full_clicked);

    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(20, 20, 20, 20);

    ui->stackedMainWidget->addWidget(m_mainSetting);
    ui->stackedMainWidget->addWidget(m_testCenter);

    // 创建 时间监视器
    timer = new QTimer(this);
    timer->setInterval(2000); // 设置超时时间为2秒

    // 连接计时器的超时信号到槽函数
    connect(timer, &QTimer::timeout, this, &MainWindow::hideWindow);


    // 启动计时器
    timer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    if(!m_isFullScreen) {

        QSize newSize = event->size();
        qDebug() << event->size().width() << event->size().height() << "before";
        int width = (int)((float)newSize.height() / 72 * 52);
        int height = (int)((float)newSize.width() / 52 * 72);

        if(width > newSize.width()) {
            this->resize(newSize.width(), height);
        } else {
            this->resize(width, newSize.height());
        }
        qDebug() << event->size().width() << event->size().height() << "after";
    }
}

double normalDistribution(double x) {
    double mean = 0.0;  // 均值
    double stdDev = 4.0;  // 标准差
    double exponent = -0.5 * pow((x - mean) / stdDev, 2);
    double coefficient = 255.0 / exp(-0.5 * pow(mean / stdDev, 2));

    double y = coefficient * exp(exponent);
    return y;
}
void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_isFullScreen){
        painter.fillRect(rect(),QBrush(QColor(0,0,0,255)));
        return ;
    }

    painter.fillRect(rect(),QBrush(QColor(0,0,0,1)));
    QRect widgetBody = ui->widgetBody->rect().translated(ui->widgetBody->mapTo(this, QPoint(0, 0)));
    QRect widgetNav = ui->widgetNav->rect().translated(ui->widgetNav->mapTo(this, QPoint(0, 0)));
    QColor backGround(255,255,255,255);

    for(int i = 10; i >= 0; -- i)
    {
        QRect leftRect(widgetBody.x() - i, widgetBody.y() - i, widgetBody.width() + i * 2, widgetBody.height() + i * 2);
        QRect rigRect(widgetNav.x() - i - 5, widgetNav.y() - i, widgetNav.width() + i * 2 + 5, widgetNav.height() + i * 2);
        QPainterPath leftPath, rigPath;
        leftPath.addRoundedRect(leftRect, i + 5, i + 5);
        rigPath.addRoundedRect(rigRect, i + 5, i + 5);
        QPainterPath mergedPath = leftPath.united(rigPath);

        int alpha = (int)normalDistribution(i + 3);
        QColor color(168, 168, 168, alpha);

        painter.setPen(color);
        if(i == 10)
            painter.setPen(Qt::red);
        if(i == 0)
            painter.setPen(Qt::blue);
        painter.drawPath(mergedPath);
        if(i == 0)
            painter.fillPath(mergedPath, backGround);
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时的位置
        m_dragStartPosition = event->globalPos();
        // 设置拖动标志
        if(!this->m_isFullScreen)
            m_isDragging = true;
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 清除拖动标志
        m_isDragging = false;
    }
    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::on_btn_full_clicked()
{
    this->m_isFullScreen = !this->m_isFullScreen;

    if(this->m_isFullScreen){

        qDebug() << "FULL";
        ui->centralwidget->setContentsMargins(0, 0, 0, 0);
        ui->widgetHeader->hide();
        ui->widgetMenu->hide();
        this->showFullScreen();


        QPoint mainWindowPos = this->mapToGlobal(QPoint(0, 0));
        qDebug() << mainWindowPos.x() << mainWindowPos.y();
        QScreen *primaryScreen = QGuiApplication::primaryScreen();
        QRect primaryScreenGeometry = primaryScreen->geometry();
        QPoint mainWindowPosOnPrimaryScreen = mainWindowPos - primaryScreenGeometry.topLeft();

        QRect fullScreenRect = this->rect();
//        QRect fullScreenRect = getRealRect(this->geometry());
        int x = mainWindowPosOnPrimaryScreen.x() + fullScreenRect.width() - m_floatingWindow->rect().width();
        int y = mainWindowPosOnPrimaryScreen.y();
        int xx = mainWindowPosOnPrimaryScreen.x();
        int yy = mainWindowPosOnPrimaryScreen.y();

        qDebug() << xx << yy;
        qDebug() << x << y;

        m_floatingWindow->move(x, y);
        m_floatingWindow->show();


    } else {

        qDebug() << "NOFULL";
//        this->showNormal();
//        this->resize(m_size);
        ui->centralwidget->setContentsMargins(20, 20, 20, 20);
        m_floatingWindow->hide();
        this->showNormal();
        ui->widgetMenu->show();
        ui->widgetHeader->show();
        this->update();
    }

}

void MainWindow::resetTimer()
{
    // 重新设置计时器
    if (timer) {
        timer->start();
    }
}

void MainWindow::hideWindow()
{
    m_floatingWindow->hide();
}

void MainWindow::on_btn_max_clicked()
{
    int nextIndex = (this->ui->stackedMainWidget->currentIndex() + 1) % this->ui->stackedMainWidget->count();
    this->ui->stackedMainWidget->setCurrentIndex(nextIndex);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {

        if(m_isFullScreen){
            // 鼠标移动时重新设置计时器
            resetTimer();
            m_floatingWindow->show();
//            qDebug() << "2 ";
        }
    }

    return QObject::eventFilter(obj, event);
}

