#ifndef SALES_H
#define SALES_H

#include "dbmanager.h"
#include <iostream>

class Sales
{
public:
    Sales();
    double getSalary(QString name);
    void setDB(DBManager* dbManager);
    int getYearsOfExpirience(QDate startDate, QDate todayDate);
    void getSubsSalary(int workerID);

private:
    DBManager* db;
    int subsSalary;
};

#endif // SALES_H
