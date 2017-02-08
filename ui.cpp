#include "ui.h"

UI::UI()
{

}

void UI::printMessage(QString message)
{
    std::cout << message.toStdString() << std::endl;
}

void UI::setDataBase(DBManager* dataBase)
{
    db = dataBase;
}

int UI::inputMainCommands()
{
    printMessage("1 - add worker");
    printMessage("2 - add subordinate to some worker");
    printMessage("3 - print worker salary");
    printMessage("4 - exit");
    int command;
    std::cin.clear();
    std::cin >> command;
    if(!(0 < command || command > 4))
    {
        QString e = "Error! Unknown command!";
        throw e;
    }
    return command;
}

void UI::recordWorker()
{
    QTextStream istream(stdin);
    printMessage("Enter the name of the worker");
    QString name;
    istream >> name;

    printMessage("Enter year of employment");
    int year;
    std::cin >> year;

    printMessage("Enter month of employment");
    int month;
    std::cin >> month;

    printMessage("Enter day of employment");
    int day;
    std::cin >> day;

    printMessage("Enter base salary");
    int salary;
    std::cin >> salary;

    printMessage("Enter employee position");
    printMessage("1 - employee");
    printMessage("2 - manager");
    printMessage("3 - sales");

    int workerTypeCode;
    std::cin >> workerTypeCode;
    QString workerType;
    switch(workerTypeCode)
    {
    case 1:
        workerType = "empoyee";
        break;
    case 2:
        workerType = "manager";
        break;
    case 3:
        workerType = "sales";
        break;
    default:
        throw "unknown command " + QString::number(workerTypeCode);
    }

    db->addWorker(name, year, month, day, salary, workerType);
}

void UI::recordSubordinate()
{
    QTextStream istream(stdin);
    printMessage("Enter superior:");
    QString superior;
    istream >> superior;

    printMessage("Enter bubordinate:");
    QString subordinate;
    istream >> subordinate;

    db->addSubordinate(superior, subordinate);
}

void UI::printWorkerSalary()
{
    QTextStream istream(stdin);
    printMessage("Enter worker name");
    QString name;
    istream >> name;

    QSqlQuery workerQuery = db->getWorker(name);
    workerQuery.next();
    QString workerType = workerQuery.value(6).toString();

    Employee employee;
    Manager manager;
    Sales sales;

    if(workerType == "employee")
    {
        setStrategy(&employee);
    }
    if(workerType == "manager")
    {
        setStrategy(&manager);
    }
    if(workerType == "sales")
    {
        setStrategy(&sales);
    }

    worker->setDB(db);
    double salary;
    salary = worker->getSalary(name);
    std::cout << salary << std::endl;
    //printMessage(salary);
}

void UI::setStrategy(IWorker* strategy)
{
    worker = strategy;
}
