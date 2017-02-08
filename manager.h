#ifndef MANAGER_H
#define MANAGER_H

#include "iworker.h"

class Manager : public IWorker
{
public:
    Manager();
    double getSalary(QString name);
    void setDB(DBManager* dbManager);
    int getYearsOfExpirience(QDate startDate, QDate todayDate);
    void getSubsSalary(int workerID);

private:
      DBManager* db;
      double subSalary;
};

#endif // MANAGER_H
