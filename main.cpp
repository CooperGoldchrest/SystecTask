#include <QCoreApplication>
#include <iostream>
#include <QDate>

#include "employee.h"
#include "manager.h"
#include "sales.h"
#include "ui.h"

int main(int argc, char *argv[])
{
    DBManager* dbManager;
    UI ui;
    ui.setDataBase(dbManager);
    bool stillWorking = true;

    try
    {
        dbManager = new DBManager();
    }
    catch (QString e)
    {
        ui.printMessage(e);
    }
    while(stillWorking)
    {
        try
        {
            int commandCode = ui.inputMainCommands();
            switch(commandCode)
            {
            case 1: ui.recordWorker();
                break;
            case 2: ui.recordSubordinate();
                break;
            case 3: ui.printWorkerSalary();
                break;
            case 4: stillWorking = false;
            }
        }
        catch (QString e)
        {
            ui.printMessage(e);
        }
    }

    return 0;
}
