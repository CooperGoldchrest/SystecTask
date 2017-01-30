#include "dbmanager.h"

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fellow_workers.db");
    db.open();
}

DBManager::~DBManager()
{
    db.close();
}

void DBManager::addWorker(QString name, QString date, int salary)
{
    QSqlQuery query;
    query.prepare("INSERT INTO main_info (name, date, base_salary)"
                    "VALUES (:name, :date, :salary)");
    query.bindValue(":name", name);
    query.bindValue(":date", date);
    query.bindValue(":salary", salary);

    query.exec();
}

void DBManager::addSubordinate(int superior_id, int subordinate_id)
{
    QSqlQuery query;

    query.exec("SELECT superior_id, subordinate_id FROM workers_hierarchy");
    if(!query.next())
    {
        query.prepare("INSERT INTO workers_hierarchy (superior_id, subordinate_id)"
                      "VALUES (:superior_id, :subordinate_id)");
        query.bindValue(":superior_id", superior_id);
        query.bindValue(":subordinate_id", subordinate_id);

        query.exec();
    }
}

QSqlQuery DBManager::getWorker(QString name)
{
    QString queryString = "SELECT id, name, date, base_salary FROM main_info WHERE "
                          "name = '" + name + "'";

    QSqlQuery query;
    query.prepare(queryString);
    query.exec();

    return query;
}

QSqlQuery DBManager::getSubordinate(int superiorID)
{
    QString queryString = "SELECT superior_id, subordinate_id FROM workers_hierarchy "
            "WHERE superior_id = " + QString::number(superiorID);

    QSqlQuery query;
    query.prepare(queryString);
    query.exec();

    while(query.next())
    {
        int supID = query.value(0).toInt();
        int subID = query.value(1).toInt();

        std::cout << supID << " " << subID << std::endl;
    }

    return query;
}
