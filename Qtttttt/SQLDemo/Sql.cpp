//.cpp
#include "Sql.h"

#include <QVariant>
#include <QSqlError>
#include <QDate>
#include <QList>
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

void Sql::bindVal(const QStringList &sl)
{
    for(int i = 0; i < 4; ++ i){
        if(!sl[i].isEmpty()){
            m_query.bindValue(valList[i], sl[i]);
        }
    }
}

void Sql::querySql(const QStringList& sl)
{
    if(!connectDatabase()){
        qDebug() << m_db.lastError().text();
    } else{

        QString condition = "WHERE ";
        bool first = false;
        for(int i = 0; i < 4; ++ i){
            if(!sl[i].isEmpty()){
               condition += descList[i] + " = " + valList[i];
               if(first && i < 3){
                   condition += " and ";
               }
               if(!first){
                   first = true;
               }
            }
        }

        QString queryQuery = "SELECT * FROM users ";
        if(first){
            queryQuery += condition;
        }
        m_query.prepare(queryQuery);
        bindVal(sl);


        if(m_query.exec()) {
            int cnt = 0;
            while(m_query.next() && cnt < 100) {
                QStringList ssl;
                ssl.append(m_query.value(0).toString());
                ssl.append(m_query.value(1).toString());
                ssl.append(m_query.value(2).toString());
                ssl.append(m_query.value(3).toString());
                ++ cnt;
                emit setWidgetItem(ssl);
            }
        } else{
            qDebug() << m_query.lastError().text();
        }
    }
    m_query.clear();
}

void Sql::insertSql(const QStringList& sl)
{
    if(!connectDatabase()){
        qDebug() << m_db.lastError().text();
    } else{

        QString desc = "(";
        QString values = "VALUES (";
        for(int i = 0; i < 4; ++ i){
            if(!sl[i].isEmpty()){
                desc += descList[i] + ',';
                values += valList[i] + ',';
            }
        }
        desc[desc.length() - 1] = ')';
        values[values.length() - 1] = ')';

        QString insertQuery = "INSERT INTO users " + desc + values;
        m_query.prepare(insertQuery);
        bindVal(sl);

        if(m_query.exec()){
            qDebug() << "OK";
        } else {
            qDebug() << m_query.lastError().text();
        }
    }
    m_query.clear();
}

void Sql::deleteSql(const QStringList& sl)
{
    if(!connectDatabase()){
        qDebug() << m_db.lastError().text();
    } else {

        QString condition = "WHERE ";
        bool first = false;
        for(int i = 0; i < 4; ++ i){
            if(!sl[i].isEmpty()){
                if(first){
                    condition += " and ";
                }
               condition += descList[i] + " = " + valList[i];
               if(!first){
                   first = true;
               }
            }
        }

        QString deleteQuery = "DELETE FROM users ";
        if(first){
            deleteQuery += condition;
        }
        m_query.prepare(deleteQuery);
        bindVal(sl);

        if(m_query.exec()){
            qDebug() << "Delete Ok.\n";
        } else {
            qDebug() << m_query.lastError().text();
        }
    }
    m_query.clear();
}

void Sql::modify(const QStringList& sl)
{
    if(!connectDatabase()){
        qDebug() << m_db.lastError().text();
    } else {

        if(sl[0].isEmpty()){
            qDebug() << "The ID does not exist";
            return ;
        }

        QString condition = "";
        bool first = false;
        for(int i = 1; i < 4; ++ i){
            if(!sl[i].isEmpty()){
               if(first){
                   condition += ", ";
               }
               condition += descList[i] + " = " + valList[i];

               if(!first){
                   first = true;
               }
            }
        }
        if(!first){
            qDebug() << "Nothing has been updated";
            return ;
        }

        QString updateQuery = "UPDATE users SET " + condition + " WHERE ID = :id";
        m_query.prepare(updateQuery);
        bindVal(sl);
        if(m_query.exec()){
            qDebug() << "Modify Ok.\n";
        } else {
            qDebug() << m_query.lastError().text();
        }
    }
    m_query.clear();
}
