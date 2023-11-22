#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
// 自定义委托类
class CustomDelegate : public QStyledItemDelegate {
public:
    // 设置Rict大小
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
        QString message = index.data(Qt::DisplayRole).toString();
//        QString message = index.data(Qt::DisplayRole).value<QString>();

        int width = 200;
        int height = message.length() * 10;

        return QSize(width, height);
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // 自定义绘制项的外观
        painter->save();

        QColor backgroundColor = QColor(255, 0, 0); // 设置为红色背景，可以根据需要修改颜色
        if (option.state & QStyle::State_Selected) {
            // 绘制选中项的背景
            painter->fillRect(option.rect, option.palette.highlight());
        }

//        painter->fillRect(option.rect, backgroundColor);

        // 绘制文本
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());

        painter->restore();
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 创建模型
    QStandardItemModel model;
    QStringListModel model_sl;
    // 设置委托
    CustomDelegate delegate;
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
