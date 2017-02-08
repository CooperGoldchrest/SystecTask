#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "iworker.h"

class Employee : public IWorker
{
public:
    Employee();
    double getSalary(QString name);
    void setDB(DBManager* dbManager);
    int getYearsOfExpirience(QDate startDate, QDate todayDate);

private:
      DBManager* db;
};

#endif // EMPLOYEE_H
