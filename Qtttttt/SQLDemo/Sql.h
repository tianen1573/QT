//.h
#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    virtual ~Sql();
    bool connectDatabase();
    void closeDatabase();
private:
    void bindVal(const QStringList& sl);
private slots:
    void querySql(const QStringList& sl);
    void insertSql(const QStringList& sl);
    void deleteSql(const QStringList& sl);
    void modifySql(const QStringList& sl);
signals:
    void setWidgetItem(const QStringList& sl);
private:
     QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
     QString m_databaseName = QString("C:\\Users\\qlz\\Desktop\\test.db");
     QSqlQuery m_query;
     bool m_connectDatabaseFlag = false;

     QStringList descList = {"ID", "NAME", "PWD", "BIR"};
     QStringList valList = {":id", ":name", ":pwd", ":bir"};
};

#endif // SQL_H
