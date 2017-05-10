#include "time.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

Time::Time(QWidget *parent) :
    QWidget(parent)
{
    //новое
    setMaximumSize(1000, 300);
    X1 = X2 = 0;
        lastIndex = -1;
        setWindowTitle(tr("Input time"));
        resize(1300, 200);
        lMarg = width()/26;
        upMarg = height()/4;


    // Инициализация массива
    for (int  i = 0; i < 10; i++){
        {
            for (int  j = 0; j < 4; j++){
                busy_time[i][j] = -1;
            }
        }

    }
    for (int i=0; i<4; i++) timeBorders[i] = 0;

   free_vec.resize(10); //инициализация

  for (int  i = 0; i < 10; i++){ // тоже инициализация

          free_vec[i].resize(4);
          for (int  j = 0; j < 4; j++){
              free_vec[i][j] = -1;
          }
      }

}

void Time::my_sort(int (*a)[4], int index)
{
    for (int i = 0; i < number_of_intvls-1; i++){
        for (int j = i; j < number_of_intvls-1/*-i*/; j++){
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
    bool flag = true;
    if (number_of_intvls == 10){
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

        for(int i = 0; i < number_of_intvls; i++){
            if(((begin_h >= busy_time[i][0] ) && (begin_h<=busy_time[i][2] ) )||
                    ((end_h <= busy_time[i][2] ) && (end_h >=busy_time[i][0] )))
            {
                flag = false;
                QMessageBox *msg = new QMessageBox(NULL);
                msg->setText("В этом промежутке вы уже заняты.");
                msg->show();
                return flag;
            }
        }
    }

    busy_time[number_of_intvls][0] = begin_h;
    busy_time[number_of_intvls][1] = begin_m;
    busy_time[number_of_intvls][2] = end_h;
    busy_time[number_of_intvls][3] = end_m;
    number_of_intvls++;

    for (int j = 0; j < 4; j++){
       my_sort(busy_time,j);
    }

    //qDebug() << "Занято: ";
//    for (int i = 0; i < number_of_intvls; i++) {
//                       qDebug() << "C " << busy_time[i][0] << " : " << busy_time[i][1] << " до " << busy_time[i][2] << " : " << busy_time[i][3];
//               }

    //qDebug() << "-----------";
    //qDebug() << "Свободно: ";

//    int free_index = 0;

//    if ((busy_time[0][0] != 0)&& (busy_time[0][1]!=0)){
//        qDebug() << "Зашел";
//        free_vec[0][0] = 0;
//        free_vec[0][1] = 0;
//        free_vec[0][2] = busy_time[0+1][0] ;
//        free_vec[0][3] = busy_time[0+1][1]-1;
//        if(free_vec[0][3] < 0){
//           // free[i][3] +=60;
//            free_vec[0][3] +=60;
//           // free[i][2]--;
//            free_vec[0][2]--;
//        }
//        free_index++;
//    }

    for(int i = 0; i < number_of_intvls-1; i++){
//        if (i ==0){

//        }
        //free[i][0] = busy_time[i][2]; //час
        free_vec[i][0] = busy_time[i][2];
        //free[i][1] = busy_time[i][3] +1; // минуты
         free_vec[i][1] = busy_time[i][3] +1;
        if (free_vec[i][1]%60 == 0){ // если было 59
           // free[i][1] = 0;
             free_vec[i][1] = 0;
            //free[i][0]++;
             free_vec[i][0]++;
        }

        //free[i][2] = busy_time[i+1][0];
        free_vec[i][2] =  busy_time[i+1][0];
        //free[i][3] = busy_time[i+1][1]-1;
        free_vec[i][3] = busy_time[i+1][1]-1;
        if(free_vec[i][3] < 0){
           // free[i][3] +=60;
            free_vec[i][3] +=60;
           // free[i][2]--;
            free_vec[i][2]--;
        }
        //free_index++;
    }

//    if((busy_time[number_of_intvls][2] != 23)&& (busy_time[number_of_intvls][3]!=59)){
//        free_vec[free_index][0] = busy_time[number_of_intvls][2];
//        free_vec[free_index][1] = busy_time[number_of_intvls][3] +1;
//        if (free_vec[free_index][1]%60 == 0){ // если было 59
//           // free[i][1] = 0;
//             free_vec[free_index][1] = 0;
//            //free[i][0]++;
//             free_vec[free_index][0]++;
//        }
//        free_vec[0][2] = 23 ;
//        free_vec[0][3] = 59;
//    }

    return flag;
}

void Time::setTimeBorders(int index, int a)
{
    timeBorders[index] = a;
}
// ДОБАВЛЕННОЕ
void Time::paintEvent(QPaintEvent *event)
{
    lMarg = width()/26;
    upMarg = height()/4;

    QPainter painter(this);
    painter.setBrush(QColor(255, 255, 255));
    //painter.drawRect(50, 50, 1200, 100);
    painter.drawRect(lMarg, upMarg, 24*lMarg, 2*upMarg);
    int x(lMarg), y(upMarg);

    for (int i=0; i<=lastIndex && i < 10; i++) {
        painter.setBrush(QColor(175, 218, 252));
        //painter.setBrush(QColor(159, 226, 191));
        //painter.setBrush(QColor(80, 200, 120));
        //painter.setBrush(QColor(255, 0, 51));
        int fromX = busy_time[i][0]*lMarg+lMarg+busy_time[i][1]*lMarg/60;
        int toX = busy_time[i][2]*lMarg+lMarg+busy_time[i][3]*lMarg/60;
        painter.drawRect(fromX, upMarg, toX-fromX, 2*upMarg);
        X1 = X2 = 0;
    }

    for (int i=0; i<=24; i++) {
        painter.drawLine(x, y, x, y+upMarg/4+3);
        painter.drawLine(x, y+2*upMarg, x, y+2*upMarg-upMarg/4-3);

        painter.drawText(x-13, y-20, 30, 20, Qt::AlignCenter, QString::number(i));
        x+=lMarg;
    }
}

void Time::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > lMarg && event->pos().x() <= width()-lMarg
            && event->pos().y() >= upMarg && event->pos().y() <= height()-upMarg)
    {
        X1 = event->pos().x();
    }
}

void Time::mouseReleaseEvent(QMouseEvent *event)
{
    if (X1 != 0 && event->pos().x()>= X1 && event->pos().x() >= lMarg)
    {
        if (event->pos().x() > width()-lMarg) X2 = width()-lMarg;
        else X2 = event->pos().x();

        lastIndex++;
        busy_time[lastIndex][0] = (X1-lMarg)/lMarg;
        qDebug() << "Start hour: " << busy_time[lastIndex][0];
        busy_time[lastIndex][1] = ((X1-lMarg)%lMarg * 60)/lMarg;
        qDebug() << "Start minute: " << busy_time[lastIndex][1];
        busy_time[lastIndex][2] = (X2-lMarg)/lMarg;
        qDebug() << "End hour: " << busy_time[lastIndex][2];
        busy_time[lastIndex][3] = ((X2-lMarg)%lMarg * 60)/lMarg;
        qDebug() << "End minute: " << busy_time[lastIndex][3];
        qDebug() << "**********************";

        update();
    }
}
