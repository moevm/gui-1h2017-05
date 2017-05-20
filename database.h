#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql>
#include <QVector>

//using namespace std;

class DataBase
{
public:
    DataBase();
    ~DataBase();
    bool addTask(QString nameOfTask, QDate deadline, int difficult, QString description, QDate currDate);//убрал Time
    QVector<QVector<QString>> cur_tasks(QDate currDate);
    QVector<QString> all_deadlines();
    //для таблицы свобоного времени
    bool add_free_user_time(QDate date_beg, QVector<QVector<int>> free_time, QDate date_end); // добавление свободного времени в бд
    QVector<QVector<int>> get_free_user_time(QDate date);//получение свободного времени из бд на конкретную дату
    //для таблицы распределенного времени
    bool add_dis_time(QDate one_date, QVector<QVector<int>> time, QString one_task_name);//добавление расредленного времени под задачу
    QVector<QVector<QString> > get_dis_time(QDate one_date); // получение распределенного времени на день вместе с названием задачи (поэтому QString)
private:
    QSqlDatabase db;



};

#endif // DATABASE_H
