#include "receiver.h"

Receiver::Receiver(QObject *parent)
    : QObject{parent}
{

}

void Receiver::SlotsDebug()
{
    qDebug() << "Myname is YiXuan\n";
}
