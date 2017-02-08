#ifndef IWORKER_H
#define IWORKER_H

#include "dbmanager.h"
#include <QDateTime>
#include <QDate>

class IWorker
{
public:
    virtual double getSalary(QString name) = 0;
    virtual void setDB(DBManager* dbManager) = 0;
    virtual int getYearsOfExpirience(QDate startDate, QDate todayDate) = 0;
};

#endif // IWORKER_H
