#include "database.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../new_GUIGUIGUI/keknaizer.sqlite");  //

    if (!db.open()) {
            qDebug() << "Что-то пошло не так!" + QDir::homePath ();
        }
    else{
        qDebug() << "Открылась!";
    }
        QVector<task> a = get_all_tasks_by_date_and_diff();
       for(int i = 0; i < a.size(); i++){
           qDebug() << a[i].getName() << " " << a[i].getDeadline()<< " " << a[i].getDifficult() << " " << a[i].getDescription();
       }
}

DataBase::~DataBase(){
    db.close();
}

bool DataBase::addTask(QString nameOfTask, QDate deadline, int difficult, QString description, QDate currDate)
{
    QSqlQuery my_query;

    my_query.prepare("INSERT INTO my_tasks (name_of_task, deadline, difficult, description, cur_date)"
                                  "VALUES (:name_of_task, :deadline, :difficult, :description, :cur_date);");

    my_query.bindValue(":name_of_task", nameOfTask);
    my_query.bindValue(":deadline", deadline);
    my_query.bindValue(":difficult", difficult);
    my_query.bindValue(":description", description);
    my_query.bindValue(":cur_date", currDate);



    if( !my_query.exec() ) {
            qDebug() << db.lastError().text();
            return false;
        }
    return true;
}

//получить все задачи в этот дедлайн
QVector<QVector<QString>> DataBase::cur_tasks(QDate currDate)
{

    QVector<QVector<QString>> for_output(30);//напишу пока тут 100
    QSqlQuery my_query;
    int i = 0;//для подсчета элементов

    my_query.prepare("SELECT name_of_task, deadline, difficult, description FROM my_tasks WHERE deadline = :currdate");
    my_query.bindValue(":currdate",currDate);
    my_query.exec();
    for (i; my_query.next();i++){
        QString name_of_task = my_query.value(0).toString();
        QString deadline = my_query.value(1).toString();
        QString difficult = my_query.value(2).toString();
        QString description = my_query.value(3).toString();

        //QString current
        qDebug() << name_of_task+","+deadline+','+difficult +","+description;
        int diff = difficult.toInt();
        switch(diff){
        case 0:
        {
            difficult = "Очень легко";
            break;
        }
        case 1:
        {
            difficult = "Легко";
            break;
        }
        case 2:{
            difficult = "Нормально";
            break;
        }
        case 3:{
            difficult = "Сложно";
            break;
        }
        case 4:
        {
            difficult = "Очень сложно";
            break;
        }
        default:
            qDebug() << "Ошибочка";

        }

        for_output[i].push_back(name_of_task);
        for_output[i].push_back(deadline);
        for_output[i].push_back(difficult);
        for_output[i].push_back(description);
        qDebug() << for_output[i][0]+","+for_output[i][1]+','+for_output[i][2] +","+for_output[i][3]+'\n';

    }


    for_output.resize (i);
    return for_output;
}

QVector<QString> DataBase::all_deadlines()
{
    QVector<QString> dates;

    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT DISTINCT deadline FROM my_tasks");

    sqlquery.exec();
    for (int i = 0; sqlquery.next();i++){
        QString deadline = sqlquery.value(0).toString();
        dates.push_back(deadline);

    }
    return dates;
}

//для таблицы свободного времени
bool DataBase::add_free_user_time(QDate date_beg, QVector<QVector<int>> free_time, QDate date_end)
{
    QDate work_date = date_beg;// рабочая переменная для даты
    QVector<int> times(4);
    int count = date_beg.daysTo(date_end); // считается количество дней между вводимой начальной датой и конечной

    for(int i = 0; i < count+1; i++){ //пока +1
        work_date = date_beg.addDays(i);// добавляем день к начальной дате( сначала 0)

        for(int j = 0; j < free_time.size(); j++){

            for(int z = 0;z < 4; z++){
                times[z]= free_time[j][z]; // записываем в рабочий вектор свободное время
            }
            QSqlQuery my_query;
            my_query.prepare("INSERT INTO free_user_time (Date, begin_hour, begin_minute, end_hour, end_minute)"
                                          "VALUES (:Date, :begin_hour, :begin_minute, :end_hour, :end_minute);");
            my_query.bindValue(":Date", work_date);
            my_query.bindValue(":begin_hour", times[0]);
            my_query.bindValue(":begin_minute", times[1]);
            my_query.bindValue(":end_hour", times[2]);
            my_query.bindValue(":end_minute", times[3]);
            if( !my_query.exec() ) {
                    qDebug() << db.lastError().text();
                    return false;
                }
        }
    }
    return true;
}

QVector<QVector<int>> DataBase::get_free_user_time(QDate date)
{
    QVector<QVector<int>> ret_freedom;
    QSqlQuery my_query;
    my_query.prepare("SELECT begin_hour, begin_minute, end_hour, end_minute FROM free_user_time WHERE Date = :date");
    my_query.bindValue(":date",date);
    my_query.exec();
    while(my_query.next()){
        ret_freedom.push_back(QVector<int>()); //запись очередного свободного промежутка - вроде так (так как типа хранится в отсортированном виде)
        ret_freedom.last().push_back(my_query.value(0).toInt());
        ret_freedom.last().push_back(my_query.value(1).toInt());
        ret_freedom.last().push_back(my_query.value(2).toInt());
        ret_freedom.last().push_back(my_query.value(3).toInt());
    }
    return ret_freedom;
}

//для таблица распределенного времени
//bool DataBase::add_dis_time(QDate one_date, QVector<QVector<int> > time, QString one_task_name)
bool DataBase::add_dis_time(QVector<freedom> distr_time)
{/*
    QVector<int> work_times(4);
    for(int i = 0; i < time.size(); i++){
        for(int z = 0;z < 4; z++){
            work_times[z]= time[i][z]; // записываем в рабочий вектор свободное время
        }*/
    for (int i = 0; i < distr_time.size(); i++) {
        QSqlQuery my_query;
        my_query.prepare("INSERT INTO distibuted_time (date, begin_task_hour, begin_task_minute, end_task_hour, end_task_minute, task_name )"
                                      "VALUES (:date, :begin_task_hour, :begin_task_minute, :end_task_hour, :end_task_minute, :task_name);");
        my_query.bindValue(":date", distr_time[i].getDate());
        my_query.bindValue(":begin_task_hour", distr_time[i].getBeg_hour());
        my_query.bindValue(":begin_task_minute", distr_time[i].getBeg_minute());
        my_query.bindValue(":end_task_hour", distr_time[i].getEnd_hour());
        my_query.bindValue(":end_task_minute", distr_time[i].getEnd_minute());
        my_query.bindValue(":task_name", distr_time[i].getTask_name());
        if( !my_query.exec() ) {
                qDebug() << db.lastError().text();
                return false;
            }
    }
    return true;
}

QVector<freedom> DataBase::get_dis_time(QDate one_date)
{
    QVector<freedom> ret_dis;
    QSqlQuery my_query;
    my_query.prepare("SELECT begin_task_hour, begin_task_minute, end_task_hour, end_task_minute, task_name  FROM distibuted_time WHERE date = :date");
    my_query.bindValue(":date",one_date);
    my_query.exec();
    while(my_query.next()){
        ret_dis.push_back(freedom()); //запись очередного свободного промежутка - вроде так (так как типа хранится в отсортированном виде)
        ret_dis.last().setDate(my_query.value(0).toDate()); // сохраняем цифвеки как QString
        ret_dis.last().setBeg_hour(my_query.value(1).toInt());
        ret_dis.last().setBeg_minute(my_query.value(2).toInt());
        ret_dis.last().setEnd_hour(my_query.value(3).toInt());
        ret_dis.last().setEnd_minute(my_query.value(4).toInt());// тут сохраняется навание задачи
        ret_dis.last().setTask_name(my_query.value(5).toString());
    }
    return ret_dis;
}

QVector<freedom> DataBase::get_all_dis_time() {

    QVector<freedom>  dis_time;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM distibuted_time  ORDER by date ");
    my_query.exec();
    while(my_query.next()){
        dis_time.push_back(freedom());
        dis_time.last().setDate(my_query.value(0).toDate());
        dis_time.last().setBeg_hour(my_query.value(1).toInt());
        dis_time.last().setBeg_minute(my_query.value(2).toInt());
        dis_time.last().setEnd_hour(my_query.value(3).toInt());
        dis_time.last().setEnd_minute(my_query.value(4).toInt());
        dis_time.last().setTask_name(my_query.value(5).toString());
    }
    return dis_time;
}

//получить все задачи, сортированные по дедлайнам и по сложности(начиная с большей)
QVector<task> DataBase::get_all_tasks_by_date_and_diff()
{
    QVector<task> ret_tasks;
    QSqlQuery my_query;
    my_query.prepare("SELECT name_of_task, deadline, difficult, description  FROM my_tasks ORDER BY deadline, difficult DESC");
    my_query.exec();
    while(my_query.next()){
        ret_tasks.push_back(task()); //запись очередного свободного промежутка - вроде так (так как типа хранится в отсортированном виде)
        ret_tasks.last().setName(my_query.value(0).toString());
        ret_tasks.last().setDeadline(my_query.value(1).toDate());
        ret_tasks.last().setDifficult(my_query.value(2).toInt());
        ret_tasks.last().setDescription(my_query.value(3).toString());
    }
    return ret_tasks;
}
//запрос на даты
QVector<QDate> DataBase::get_free_dates()
{
    QVector<QDate> ret_free_dates;
    QSqlQuery my_query;
    my_query.prepare("SELECT Date FROM free_user_time  GROUP by Date ");
    my_query.exec();
    while(my_query.next()){
        ret_free_dates.push_back((my_query.value(0).toDate()));
    }
    return ret_free_dates;
}

bool DataBase::delete_same_dates(QDate begin, QDate end, QVector<QDate> times)
{
    int count_dates = begin.daysTo(end);
     QSqlQuery my_query;
     QDate work_date;

    for(int i = 0; i < count_dates+1; i++){
        work_date = begin.addDays(i);
        qDebug() << work_date;
        if (times.contains(work_date)){
            my_query.prepare("DELETE  FROM free_user_time WHERE Date = :new_date ");
            my_query.bindValue(":new_date", work_date);
            if( !my_query.exec() ) {
                    qDebug() << db.lastError().text();
                    return false;
                }
        }

    }
    return true;
}

QVector<freedom> DataBase::all_free_times()
{
    QVector<freedom>  ret_free;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM free_user_time  ORDER by Date ");
    my_query.exec();
    while(my_query.next()){
        ret_free.push_back(freedom());
        ret_free.last().setDate(my_query.value(0).toDate());
        ret_free.last().setBeg_hour(my_query.value(1).toInt());
        ret_free.last().setBeg_minute(my_query.value(2).toInt());
        ret_free.last().setEnd_hour(my_query.value(3).toInt());
        ret_free.last().setEnd_minute(my_query.value(4).toInt());
        ret_free.last().setTask_name(my_query.value(5).toString());
    }
    return ret_free;
}

bool DataBase::delete_and_insert_in_dis_time(QVector<freedom> distr_time)
{
    //удаление
    QSqlQuery my_query;
    my_query.prepare("DELETE  FROM distibuted_time ");
    if( !my_query.exec() ) {
            qDebug() << db.lastError().text() << "FAIL IN DELETING";
            return false;
        }
    //добавление

    for(int i = 0; i < distr_time.size(); i++){

        my_query.prepare("INSERT INTO distibuted_time (date, begin_task_hour, begin_task_minute, end_task_hour, end_task_minute, task_name)"
                                      "VALUES (:date, :begin_task_hour, :begin_task_minute, :end_task_hour, :end_task_minute, :task_name);");
        my_query.bindValue(":date", distr_time[i].getDate());
        my_query.bindValue(":begin_task_hour", distr_time[i].getBeg_hour());
        my_query.bindValue(":begin_task_minute", distr_time[i].getBeg_minute());
        my_query.bindValue(":end_task_hour", distr_time[i].getEnd_hour());
        my_query.bindValue(":end_task_minute", distr_time[i].getEnd_minute());
        my_query.bindValue(":task_name", distr_time[i].getTask_name());
        if( !my_query.exec() ) {
                qDebug() << db.lastError().text() << "FAIL IN INSERTING";
                return false;
            }

    }
    return true;

}
