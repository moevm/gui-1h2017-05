#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql>

//using namespace std;

class DataBase
{
public:
    DataBase();
    ~DataBase();
    bool addTask(QString nameOfTask, QDate deadline, int difficult, QString description, QDate currDate);//убрал Time
    QVector<QVector<QString>> cur_tasks(QDate currDate);
    QVector<QString> all_deadlines();
private:
    QSqlDatabase db;



};

#endif // DATABASE_H
