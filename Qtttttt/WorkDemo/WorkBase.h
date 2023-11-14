#ifndef WORKBASE_H
#define WORKBASE_H

#include <QObject>
#include <QStackedWidget>


class WorkBase : public QObject
{
    Q_OBJECT
public:
    explicit WorkBase(QStackedWidget* stackwidget, QObject *parent = nullptr);

    virtual void start() = 0;

    void stackedRemovceAll();

signals:
    void next();
    void back();

protected:
    QStackedWidget* m_stackWidget;
};

#endif // WORKBASE_H
