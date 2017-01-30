#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QVariant>
#include <iostream>

//TODO make this feel lonely
class DBManager
{
public:
    DBManager();
    ~DBManager();
    void addWorker(QString name, QString date, int salary);
    void addSubordinate(int superior_id, int subordinate_id);
    QSqlQuery getWorker(QString name);
    QSqlQuery getSubordinate(int superiorID);

private:
    QSqlDatabase db;
    static DBManager *instance;
};

#endif // DBMANAGER_H
