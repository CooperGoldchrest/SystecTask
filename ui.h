#ifndef UI_H
#define UI_H

#include "dbmanager.h"
#include "iworker.h"
#include "employee.h"
#include "manager.h"
#include "sales.h"
#include <iostream>
#include <QTextStream>

class UI
{
public:
    UI();
    void printMessage(QString message);
    void setDataBase(DBManager* dataBase);
    int inputMainCommands();
    void recordWorker();
    void recordSubordinate();
    void printWorkerSalary();
    void setStrategy(IWorker* strategy);//or set worker

private:
    DBManager* db;
    IWorker* worker;
};

#endif // UI_H
