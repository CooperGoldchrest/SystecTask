#include "sales.h"

Sales::Sales()
{

}

double Sales::getSalary(QString name)
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

    double allowance = base_salary * 0.01 * (experience >= 35 ? 35 : experience);
    subsSalary = 0;
    getSubsSalary(query.value(0).toInt());

    double salary = allowance + base_salary + (subsSalary * 0.003);

    return salary;
}

void Sales::setDB(DBManager *dbManager)
{
    db = dbManager;
}

int Sales::getYearsOfExpirience(QDate startDate, QDate todayDate)
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

void Sales::getSubsSalary(int workerID)
{
    QSqlQuery query = db->getSubordinate(workerID);
    while(query.next())
    {
        int subordinate_id = query.value(1).toInt();
        QSqlQuery worker = db->getWorker(subordinate_id);
        worker.next();
        subsSalary += worker.value(5).toDouble();
        getSubsSalary(subordinate_id);
    }
}
