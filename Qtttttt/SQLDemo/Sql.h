#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    virtual ~Sql();
    bool connectDatabase();
    void closeDatabase();
private slots:
    void querySql();
    void insertSql();
    void deleteSql(const QString& key);
signals:
    void initTableWidget();
    void setWidgetItem(const QStringList& sl);
private:
     QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
     QString m_databaseName = QString("C:\\Users\\qlz\\Desktop\\Photos.sqlite");
     bool m_connectDatabaseFlag = false;
};

#endif // SQL_H
