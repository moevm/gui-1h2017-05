#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql>

class DataBase
{
public:
    DataBase();
    ~DataBase();
    bool addTask(QString nameOfTask, QDate deadline, int difficult, QString description, QString currDate);
private:
    QSqlDatabase db;


};

#endif // DATABASE_H
