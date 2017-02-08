#include "dbmanager.h"

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fellow_workers.db");
    if(!db.open())
    {
        QString e = "Cannot open the Data Base";
        throw e;
    }
}

DBManager::~DBManager()
{
    db.close();
}

void DBManager::addWorker(QString name, int year, int month, int day, double salary, QString wType)
{
    QSqlQuery query;
    query.prepare("INSERT INTO main_info (name, year, month, day, base_salary, worker_Type) "
                  "VALUES (:name, :year, :month, :day, :salary, :type)");
    query.bindValue(":name", name);
    query.bindValue(":year", year);
    query.bindValue(":month", month);
    query.bindValue(":day", day);
    query.bindValue(":salary", salary);
    query.bindValue(":type", wType);

    if(!query.exec())
    {
        QString e = "Cannot add worker";
        throw e;
    }
}

void DBManager::addSubordinate(QString superior, QString subordinate)
{
    QSqlQuery query;
    int superior_id ;
    int subordinate_id;

    //checking data
    query = getWorker(superior);
    query.exec();
    if(query.next())
    {
        if(query.value(6).toString() == "employee")
        {
            QString e = "Worker " + superior + " cannot be a superior";
            throw e;
        }
        superior_id = query.value(0).toInt();
    }
    else
    {
        QString e = "There is not worker " + superior + " in database";
        throw e;
    }
    query.finish();

    query = getWorker(subordinate);
    query.exec();

    if(query.next())
    {
        subordinate_id = query.value(0).toInt();
        if(superior_id == subordinate_id)
        {
            QString e = "Worker " + query.value(1).toString() + " cannot subbordinate himself";
            throw e;
        }
    }
    else
    {
        QString e = "There is not worker " + subordinate + " in database";
        throw e;
    }

    //adding data
    query.prepare("INSERT INTO workers_hierarchy (superior_id, subordinate_id)"
                  "VALUES (:superior_id, :subordinate_id)");
    query.bindValue(":superior_id", superior_id);
    query.bindValue(":subordinate_id", subordinate_id);

    if(!query.exec())
    {
        QString e = "Cannot add subordinate";
        throw e;
    }
}

QSqlQuery DBManager::getWorker(QString name) const
{
    QString queryString = "SELECT id, name, year, month, day, base_salary, worker_type"
                          " FROM main_info WHERE name = '" + name + "'";

    QSqlQuery query;
    query.prepare(queryString);
    if(!query.exec())
    {
        QString e = "Cannot get worker";
        throw e;
    }

    return query;
}

QSqlQuery DBManager::getWorker(int id) const
{
    QString queryString = "SELECT id, name, year, month, day, base_salary, worker_type"
                          " FROM main_info WHERE id = " + QString::number(id);

    QSqlQuery query;
    query.prepare(queryString);
    if(!query.exec())
    {
        QString e = "Cannot get worker";
        throw e;
    }

    return query;
}

QSqlQuery DBManager::getSubordinate(int superiorID) const
{
    QString queryString = "SELECT superior_id, subordinate_id FROM workers_hierarchy "
            "WHERE superior_id = " + QString::number(superiorID);

    QSqlQuery query;
    query.prepare(queryString);
    if(!query.exec())
    {
        QString e = "Cannot get subordinate";
        throw e;
    }

    return query;
}
