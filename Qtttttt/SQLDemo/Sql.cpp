#include "Sql.h"

#include <QSqlQuery>
#include <QVariant>
Sql::Sql(QObject *parent)
    : QObject{parent}
{

}

Sql::~Sql()
{
    closeDatabase();
}

bool Sql::connectDatabase()
{
    if(!m_connectDatabaseFlag){
        m_db.setDatabaseName(m_databaseName);
        m_connectDatabaseFlag = m_db.open();
    }

    return m_connectDatabaseFlag;
}

void Sql::closeDatabase()
{
    m_db.close();
    m_connectDatabaseFlag = false;
}

void Sql::querySql()
{
    if(!connectDatabase()){
        int k = 0;
//        QMessageBox::information(this, "Error", "Failed to connect to database");
    } else{
        QSqlQuery query;
        if(query.exec("SELECT Z_PK, Z_OPT, ZTRASHEDDATE, ZUUID FROM ZASSET")) {
            int cnt = 0;
            while(query.next() && cnt < 100) {
                QStringList sl;
                sl.append(query.value(0).toString());
                sl.append(query.value(1).toString());
                sl.append(query.value(2).toString());
                sl.append(query.value(3).toString());
                ++ cnt;
                emit setWidgetItem(sl);
            }
            query.clear();
        } else{
            ;//
        }
    }
}

void Sql::insertSql()
{
    QSqlQuery query;
//    QString sql = "INSERT INTO ZASSET values(1, )"
}

void Sql::deleteSql(const QString& key)
{
    QSqlQuery query;
    QString sql = "DELETE FROM ZASSET WHERE O_PK = " + key;
    if(query.exec(sql)){
        qDebug() << "Delete Ok.\n";
    } else {
        qDebug() << "Delete Fail.\n";
    }
}
