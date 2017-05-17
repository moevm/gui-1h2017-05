#include "database.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../new_GUIGUIGUI/keknaizer.sqlite");  //тут путь

    if (!db.open()) {
            qDebug() << "Что-то пошло не так!" + QDir::homePath ();
        }
    else{
        qDebug() << "Открылась!";
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

