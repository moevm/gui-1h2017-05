#include "database.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/keknaizer.sqlite");  //тут путь

    if (!db.open()) {
            qDebug() << "Что-то пошло не так!" + QDir::homePath ();
        }
    else{
        qDebug() << "Открылась!";
    }

 //   if (!db.open()) {
 //         qDebug() << db.lastError().text();
  //  }

    //qDebug() << "Я СОЗДАЛСЯ";
    //QSqlQuery db_query;
       // DDL query
//   QString str = "CREATE TABLE my_tasks ("
//           "number integer PRIMARY KEY AUTOINCREMENT, "
//           "name_of_task VARCHAR(50), "
//           "deadline TIMESTAMP, "
//           "difficult INTEGER, "
//           "description VARCHAR(255), "
//           "cur_date TIMESTAMP, "
//           ");";

  //  QSqlQuery query;
    //("SELECT * FROM my_tasks");
  //  if(!query.exec("SELECT * FROM my_tasks")){
  //      qDebug() << "НУ СУКА НУ КУДА БЛЯТЬ ТЫ ЛЕЗЕШЬ НАХУЙ";
   // }
    //query.exec();
   // int idNum = query.record().indexOf("number");
    //int idName = query.record().indexOf("name_of_task");
//    int idName = query.record().indexOf("name_of_task");
//    int idName = query.record().indexOf("name_of_task");
    //while(query.next())
  // {
      // QString name = query.value(idNum).toString();
     //  qDebug() << name;
      // qDebug() << "не охуеть блять";
   // }
       QSqlQuery query;
       query.exec("SELECT name_of_task, difficult, description FROM my_tasks");

       //Выводим значения из запроса
       while (query.next())
        {
       QString name_of_task = query.value(0).toString();
       QString difficult = query.value(1).toString();
       QString description = query.value(2).toString();
       qDebug() << name_of_task+","+difficult +","+description+'\n';
        }



//   bool b = db_query.exec(str);
//   if (!b) {
//       qDebug() << "Вроде не удается создать таблицу, провертье карманы!";
//   }



       //Осуществляем запрос


}

DataBase::~DataBase(){
    db.close();
}

