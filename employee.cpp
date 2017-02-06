#include "employee.h"

Employee::Employee()
{

}

double Employee::getSalary(QString name)
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

    double allowance = base_salary * 0.03 * (experience >= 10 ? 10 : experience);

    double salary = allowance + base_salary;

    return salary;
}

void Employee::setDB(DBManager* dbManager)
{
    db = dbManager;
}

int Employee::getYearsOfExpirience(QDate startDate, QDate todayDate)
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
