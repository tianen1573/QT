#include <QDebug>
#include <QString>

void func(const QString& qstr)
{
    qDebug() << qstr;
}

int main(int argc, char *argv[])
{

    QString str1("ABCD");
    char * buff = str1.toUtf8().data();
    func(buff);
    return 0;
}
