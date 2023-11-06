#ifndef POINTERQWIDGET_H
#define POINTERQWIDGET_H

#include <QObject>
#include <QWidget>

class PointerQWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PointerQWidget(QWidget *parent = nullptr);

    void init();

    void paintEvent(QPaintEvent *event);
};

#endif // POINTERQWIDGET_H
