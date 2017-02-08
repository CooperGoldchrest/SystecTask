#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
//This class was supposed to be a singleton, but I'm confused in architecture
//and I am afraid to break something
class DBManager
{
public:
    DBManager();
    ~DBManager();
    DBManager getInstance();
    void addWorker(QString name, int year, int month, int day, double salary, QString wType);
    void addSubordinate(QString superior, QString subordinate);
    QSqlQuery getWorker(QString name) const;
    QSqlQuery getWorker(int id) const;
    QSqlQuery getSubordinate(int superiorID) const;

private:
    QSqlDatabase db;
};


#endif // DBMANAGER_H
