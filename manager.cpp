#include "manager.h"

Manager::Manager()
{

}

double Manager::getSalary(QString name)
{
    QSqlQuery query = db->getWorker(name);
    query.next();

    int year = query.value(2).toInt();
    int month = query.value(3).toInt();
    int day = query.value(4).toInt();
    double base_salary = query.value(5).toDouble();

    QDate startDate(year, month, day);
    QDate todayDate = QDate::currentDate();
    int experience = getYearsOfExpirience(startDate, todayDate);

    double allowance = base_salary * 0.05 * (experience >= 8 ? 8 : experience);//5% * 8 = 40%
    subSalary = 0;
    getSubsSalary(query.value(0).toInt());

    double salary = allowance + base_salary + (subSalary * 0.005);

    return salary;
}

void Manager::setDB(DBManager* dbManager)
{
    db = dbManager;
}

int Manager::getYearsOfExpirience(QDate startDate, QDate todayDate)
{
    int years = todayDate.year() - startDate.year();
    int months = todayDate.month() - startDate.month();
    int days = todayDate.day() - startDate.day();
    if(years > 0)
    {
        if(months <= 0)
        {
            years--;
        }
        else
        {
            if(days < 0)
            {
                years--;
            }
        }
    }
    return years;
}

void Manager::getSubsSalary(int workerID)
{
    QSqlQuery query = db->getSubordinate(workerID);
    while(query.next())
    {
        int subordinate_id = query.value(1).toInt();
        QSqlQuery worker = db->getWorker(subordinate_id);
        worker.next();
        QString workerType = worker.value(6).toString();
        if(workerType == "employee")
        {
            subSalary += worker.value(5).toDouble();
        }
        else
        {
            getSubsSalary(subordinate_id);
        }
    }
}
