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
    bool addTask(QString nameOfTask, QDateTime deadline, int difficult, QString description, QDateTime currDate);//убрал Time
    QVector<QVector<QString>> cur_tasks(QDateTime currDate);
private:
    QSqlDatabase db;



};

#endif // DATABASE_H
