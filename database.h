#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql>
#include <QVector>
#include <task.h>
#include <freedom.h>

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
    bool add_dis_time(QVector<freedom> distr_time);//добавление расредленного времени под задачу
    QVector<freedom> get_dis_time(QDate one_date); // получение распределенного времени на день вместе с названием задачи (поэтому QString)
    QVector<freedom> get_all_dis_time();

    QVector<task> get_all_tasks_by_date_and_diff();

    QVector<QDate> get_free_dates();

    bool delete_same_dates(QDate begin, QDate end, QVector<QDate> times);

    //для Сержа
    QVector<freedom> all_free_times();
//    bool delete_and_insert_in_free_time(QVector<freedom> my_freedom);
    bool DataBase::delete_and_insert_in_dis_time(QVector<freedom> distr_time);
private:
    QSqlDatabase db;



};

#endif // DATABASE_H
