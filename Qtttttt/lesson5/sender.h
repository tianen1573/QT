#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

signals:
    void SignalDebug();
};

#endif // SENDER_H
