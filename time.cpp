#include "time.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

Time::Time(QWidget *parent) :
    QWidget(parent)
{
    for (int i=0; i<4; i++) timeBorders[i] = 0;

    borders[0] = borders[1] = false; //ПРОВЕРИТЬ

}

void Time::my_sort(QVector<QVector<int>> &a, int index)
{
    QVector<int> work_var(4);
    for (int i = 0; i < a.size()-1; i++){
        for (int j = i; j < a.size()-1/*-i*/; j++){
            if (index == 0){
                    if (a[i][index] >  a[j+1][index])
                    {
                        //обмен значениями (в 3 цикла)
                        for (int z =0; z < 4; z++){
                             work_var[z] = a[i][z];
                        }
                        for (int z =0; z < 4; z++){
                            a[i][z] = a[j+1][z];
                        }

                        for(int z =0; z < 4; z++){
                            a[j+1][z] = work_var[z];
                        }

                    }
            }
            else if (index == 1){
                if ((a[i][index-1] == a[j+1][index-1]) &&(a[i][index] >  a[j+1][index]))
                {
                    //обмен значениями (в 3 цикла)
                    for (int z =0; z < 4; z++){
                         work_var[z] = a[i][z];
                    }
                    for (int z =0; z < 4; z++){
                        a[i][z] = a[j+1][z];
                    }

                    for(int z =0; z < 4; z++){
                        a[j+1][z] = work_var[z];
                    }
                }
            }
            else if (index == 2){
                if ((a[i][index-2] == a[j+1][index-2]) && (a[i][index-1] ==  a[j+1][index-1]) &&(a[i][index] >  a[j+1][index]))
                {
                    //обмен значениями (в 3 цикла)
                    for (int z =0; z < 4; z++){
                         work_var[z] = a[i][z];
                    }
                    for (int z =0; z < 4; z++){
                        a[i][z] = a[j+1][z];
                    }
                    for(int z =0; z < 4; z++){
                        a[j+1][z] = work_var[z];
                    }
                }
            }
            else if (index == 3){
                if ((a[i][index-3] == a[j+1][index-3]) && (a[i][index-2] ==  a[j+1][index-2]) && (a[i][index-1] ==  a[j+1][index-1]) &&(a[i][index] >  a[j+1][index]))
                {
                    //обмен значениями (в 3 цикла)
                    for (int z =0; z < 4; z++){
                         work_var[z] = a[i][z];
                    }
                    for (int z =0; z < 4; z++){
                        a[i][z] = a[j+1][z];
                    }

                    for(int z =0; z < 4; z++){
                        a[j+1][z] = work_var[z];
                    }
                }
            }
        }
    }
}

bool Time::free_time()
{
    int begin_h, begin_m, end_h, end_m;
    begin_h = timeBorders[0];
    begin_m = timeBorders[1];
    end_h = timeBorders[2];
    end_m = timeBorders[3];

    //добавлю вектор
    QVector<int> time_from_user(4);
    time_from_user.push_back(begin_h);
    time_from_user.push_back(begin_m);
    time_from_user.push_back(end_h);
    time_from_user.push_back(end_m);

    bool flag = true;
    if (busy_time.size() == 10){
        //qDebug() << "Take it easy, maaan.";
        flag = false;
        return flag;
    }
    else if ((end_h < begin_h ) || ((begin_h == end_h) && (end_m <begin_m )) ){

        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Неверно введено время.");
        msg->show();
        flag = false;
        return flag;
    }
    else {

        for(int i = 0; i < busy_time.size(); i++){
            qDebug() <<((end_h < busy_time[i][2]) && (end_h > busy_time[i][0]))<<//  конечный в промежутке
                    ((begin_h > busy_time[i][0]) && (begin_h < busy_time[i][2]) )<<// нача час в промежутке
                    ((end_h == /*begin_h ==*/ busy_time[i][0]) && ( end_m > busy_time[i][1]) && (begin_h < busy_time[i][0] || (begin_h ==busy_time[i][0] && begin_m < busy_time[i][3] ))   )<< //в начале часа
                    ((/*end_h ==*/ begin_h == busy_time[i][2]) && ( begin_m < busy_time[i][3]) && (end_h > busy_time[i][2] || (end_h == busy_time[i][2] && end_m >busy_time[i][1] )) )<<
                    (begin_h == busy_time[i][0] && ( begin_m > busy_time[i][1]))<<
                    (end_h  == busy_time[i][2] && end_m < busy_time[i][3])<<
                    (begin_h >= busy_time[i][0] && end_h <= busy_time[i][2] && begin_h != end_h) <<
                    (begin_h <= busy_time[i][0] && (end_h >= busy_time[i][2]) && begin_h != end_h)
                    ;

            if(
                    ((end_h < busy_time[i][2]) && (end_h > busy_time[i][0]))||//  конечный в промежутке
                    ((begin_h > busy_time[i][0]) && (begin_h < busy_time[i][2]) )|| // нача час в промежутке
                    ((end_h == /*begin_h ==*/ busy_time[i][0]) && ( end_m > busy_time[i][1]) && (begin_h < busy_time[i][0] || (begin_h ==busy_time[i][0] && begin_m < busy_time[i][3] ))   )|| //в начале часа
                    ((/*end_h ==*/ begin_h == busy_time[i][2]) && ( begin_m < busy_time[i][3]) && (end_h > busy_time[i][2] || (end_h == busy_time[i][2] && end_m >busy_time[i][1] )) )||
                    (begin_h == busy_time[i][0] && ( begin_m > busy_time[i][1]) && end_h!=begin_h)|| //??????
                    (end_h  == busy_time[i][2] && end_m < busy_time[i][3]  && end_h!=begin_h )||
                    (begin_h >= busy_time[i][0] && end_h <= busy_time[i][2] && begin_h != end_h) ||
                    (begin_h <= busy_time[i][0] && (end_h >= busy_time[i][2]) && begin_h != end_h)// ??????
                    )
            {

                flag = false;
                QMessageBox *msg = new QMessageBox(NULL);
                msg->setText("В этом промежутке вы уже заняты.");
                msg->show();
                return flag;
            }
        }
    }

    busy_time.push_back(QVector<int>());
    busy_time.last().push_back(begin_h);
    busy_time.last().push_back(begin_m);
    busy_time.last().push_back(end_h);
    busy_time.last().push_back(end_m);
    //number_of_intvls++;
    qDebug() <<busy_time;

    for (int j = 0; j < 4; j++){
       my_sort(busy_time,j);
    }

    //qDebug() << "Занято: ";
//    for (int i = 0; i < busy_time.si; i++) {
//                       //qDebug() << "C " << busy_time[i][0] << " : " << busy_time[i][1] << " до " << busy_time[i][2] << " : " << busy_time[i][3];
//               }
    qDebug() << busy_time;
    qDebug() << free_vec.size();

    if (((busy_time[0][0] != 0)) || ((busy_time[0][0] == 0)&& (busy_time[0][1]!=0)) ){ // подумать как быть с изменением
            if(borders[0] == false){

                free_vec.push_front(QVector<int>()); //вставить в начало
                free_vec.first().push_back(0);
                free_vec.first().push_back(0);
                free_vec.first().push_back(busy_time[0][0]);
                free_vec.first().push_back(busy_time[0][1]); //пока уберу -1
            }
            else if(borders[0]== true){
                free_vec.first()[0] = (0);
                free_vec.first()[1] = (0);
                free_vec.first()[2] = (busy_time[0][0]);
                free_vec.first()[3] = (busy_time[0][1]); //пока уберу -1
            }

//            if(free_vec[0][3] < 0){ // ЭТО БЫЛО ДЛЯ  -1
//               // free[i][3] +=60;
//                free_vec[0][3] +=60;
//               // free[i][2]--;
//                free_vec[0][2]--;
//            }

            borders[0] = true;
       // }

       // free_index++;
    }

    //ВОЗМОЖНО
    if((busy_time[0][0] == 0)&& (busy_time[0][1]==0)){
        if(borders[0] == true){
            free_vec.erase(free_vec.begin());
            borders[0] = false;
        }

    }

    //Правая граница
    qDebug() << "  ДО правой границы " << free_vec;

    if((busy_time.last()[2] != 23) || (busy_time.last()[2] == 23)&& (busy_time.last()[3]!=59)){

        if (borders[1] == false){
            free_vec.push_back(QVector<int>());
            free_vec.last().push_back(busy_time.last()[2]) ;
            free_vec.last().push_back(busy_time.last()[3]) ; // ПОКА УБРАЛ +1 И ТО, ЧТО НИЖЕ
    //        if (free_vec[free_index][1]%60 == 0){ // если было 59
    //           // free[i][1] = 0;
    //             free_vec[free_index][1] = 0;
    //            //free[i][0]++;
    //             free_vec[free_index][0]++;
    //        }
            free_vec.last().push_back(23) ;
            free_vec.last().push_back(59);
        }
        else if(borders[1] == true){
            free_vec.last()[0] = (busy_time.last()[2]) ;
            free_vec.last()[1] = (busy_time.last()[3]) ; // ПОКА УБРАЛ +1 И ТО, ЧТО НИЖЕ
            free_vec.last()[2] = (23) ;
            free_vec.last()[3] = (59);
        }
        borders[1] = true;
    }

    //ВОЗМОЖНО 2 !
    if((busy_time.last()[2] == 23)&& (busy_time.last()[3]==59)){
        if(borders[1] == true){
            free_vec.erase(free_vec.end()-1); //-1, потому что end - на 1 больше
            borders[1] = false;
        }
    }

    int k = 0;
    int j;
    if(borders[0] == true)
        {
        // учет границы левой
        k = 1 ;
    }
    else
        k = 0;

    j = busy_time.size()-1;
    qDebug() << j ;

    if(borders[0] && borders[1]){
        free_vec.erase(free_vec.begin()+1,free_vec.end()-1); //удалить все кроме левой и правой границы
        qDebug() << "Первое условие!";
    }
    else if(borders[0]){
        free_vec.erase(free_vec.begin()+1,free_vec.end());//удалить все, кроме левой, так как нет правой
         qDebug() << "Второе условие!";
    }
    else if(borders[1]){
        free_vec.erase(free_vec.begin(),free_vec.end()-1);//удалить все, кроме правой, так как нет левой ?? ТУТ ХЗ
         qDebug() << "Третье условие!";
    }
    else{
        free_vec.clear(); // УДАЛИТЬ ВСЕ, так как нет границ, ты свободен, малыш
         qDebug() << "Четвертое условие!";
    }


    //borders[1] == true ? j = busy_time.size()-1 : j = busy_time.size()-2; //учет границы правой
    bool del = false;
    for(int i = 0; i < j; i++){
    qDebug() << "ZAZAZAZAZZ";
        if(!((busy_time[i][2] == busy_time[i+1][0]) && (busy_time[i][3] ==busy_time[i+1][1] )))
        {
            if(!free_vec.empty() && !del){
                free_vec.insert(free_vec.end()-1,QVector<int>()); //ПРОБУЕММ end
            }
            else {
                free_vec.push_back(QVector<int>());
                del = true;
            }
            qDebug() << "ПРоверка после вставки!! " << free_vec;
            free_vec[i+k].push_back(busy_time[i][2]);
             free_vec[i+k].push_back(busy_time[i][3]) ; // УБРАЛ +1
            free_vec[i+k].push_back(busy_time[i+1][0]);
            free_vec[i+k].push_back(busy_time[i+1][1]); //УБРАЛ -1
        }
    }
    del = false;
    return flag;
}

void Time::setTimeBorders(int index, int a)
{
    timeBorders[index] = a;
}
