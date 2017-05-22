#include "time.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QDateTime>

Time::Time(QWidget *parent) : //ДОБАВИТЬ, ЧТОБЫ НЕЛЬЗЯ БЫЛО ВНОСИТ ОДИНАКОВЫЕ ДАТЫ НАЧАЛА И КОНЦА
    QWidget(parent)
{
    //новое
    //setMaximumSize(1000, 300);
    X1 = X2 = 0;
        setWindowTitle(tr("Input time"));
        resize(1300, 200);
        lMarg = width()/14;
        upMarg = height()/8;

    for (int i=0; i<4; i++) timeBorders[i] = 0;

    borders[0] = borders[1] = false; //ПРОВЕРИТЬ
    isClickable = false;
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
    /*if (busy_time.size() == 10){
        //qDebug() << "Take it easy, maaan.";
        flag = false;
        return flag;
    }
    else */
    if( begin_h == end_h && begin_m == end_m){
        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Неверно введено время.");
        msg->show();
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
//            qDebug() <<(QTime(begin_h,begin_m) <= QTime(busy_time[i][0], busy_time[i][1]) && QTime(end_h,end_m) >= QTime(busy_time[i][2],busy_time[i][3])) <<
//                    (QTime(end_h,end_m) <= QTime(busy_time[i][2],busy_time[i][3]) && QTime(end_h,end_m) > QTime(busy_time[i][0], busy_time[i][1])) <<
//                     (QTime(begin_h,begin_m) >= QTime(busy_time[i][0], busy_time[i][1]) && QTime(begin_h,begin_m) < QTime(busy_time[i][2],busy_time[i][3]) ) <<
//                      (QTime(begin_h,begin_m) > QTime(busy_time[i][0], busy_time[i][1]) && QTime(end_h,end_m) < QTime(busy_time[i][2],busy_time[i][3]) )
//                    ;

            if(  (QTime(begin_h,begin_m) <= QTime(busy_time[i][0], busy_time[i][1]) && QTime(end_h,end_m) >= QTime(busy_time[i][2],busy_time[i][3])) ||
                  (QTime(end_h,end_m) <= QTime(busy_time[i][2],busy_time[i][3]) && QTime(end_h,end_m) > QTime(busy_time[i][0], busy_time[i][1])) ||
                   (QTime(begin_h,begin_m) >= QTime(busy_time[i][0], busy_time[i][1]) && QTime(begin_h,begin_m) < QTime(busy_time[i][2],busy_time[i][3]) ) ||
                    (QTime(begin_h,begin_m) > QTime(busy_time[i][0], busy_time[i][1]) && QTime(end_h,end_m) < QTime(busy_time[i][2],busy_time[i][3]) )
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

   // qDebug() <<busy_time;

    for (int j = 0; j < 4; j++){
       my_sort(busy_time,j);
    }

//    qDebug() << busy_time;
//    qDebug() << free_vec.size();

    qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ДО проверки начального" << free_vec;

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
            borders[0] = true;
    }


    qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ПОСЛЕ проверки начального" << free_vec;

    //ВОЗМОЖНО
    if((busy_time[0][0] == 0)&& (busy_time[0][1]==0)){
        if(borders[0] == true){
            free_vec.remove(0); // заменяю на remove
            borders[0] = false;
        }

    }

    qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ПОСЛЕ проверки НА УДАЛЕНИЕ НАЧАЛЬНОГО" << free_vec;


    if((busy_time.last()[2] != 23) || (busy_time.last()[2] == 23)&& (busy_time.last()[3]!=59)){

        if (borders[1] == false){
            free_vec.push_back(QVector<int>());
            free_vec.last().push_back(busy_time.last()[2]) ;
            free_vec.last().push_back(busy_time.last()[3]) ; // ПОКА УБРАЛ +1 И ТО, ЧТО НИЖЕ
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

        qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ПОСЛЕ проверки КОНЕЧНОГО" << free_vec;

    //ВОЗМОЖНО 2 !
    if((busy_time.last()[2] == 23)&& (busy_time.last()[3]==59)){
        if(borders[1] == true){
            free_vec.remove(free_vec.size()-1); //-1, потому что end - на 1 больше
            borders[1] = false;
        }
    }

           qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ПОСЛЕ проверки НА УДАЛЕНИЕ КОНЕЧНОГО" << free_vec;

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
        free_vec.remove(1,free_vec.size()-2); //удалить все кроме левой и правой границы
        qDebug() << "Первое условие!";
    }
    else if(borders[0]){
        free_vec.remove(1,free_vec.size()-1);//удалить все, кроме левой, так как нет правой
         qDebug() << "Второе условие!";
    }
    else if(borders[1]){
        free_vec.remove(0,free_vec.size()-1);//удалить все, кроме правой, так как нет левой ?? ТУТ ХЗ
         qDebug() << "Третье условие!";
    }
    else{
        free_vec.clear(); // УДАЛИТЬ ВСЕ, так как нет границ, ты свободен, малыш
         qDebug() << "Четвертое условие!";
    }


    qDebug() << "Вывод  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ ПОСЛЕ проверки границ и очистки" << free_vec;


    //borders[1] == true ? j = busy_time.size()-1 : j = busy_time.size()-2; //учет границы

    QVector<int> wwwork;

    bool del = false;
    for(int i = 0; i < j; i++){  //ОШИБКА ВОЗНИКАеТ В ЭТОМ ЦИКЛЕ
        if(!((busy_time[i][2] == busy_time[i+1][0]) && (busy_time[i][3] ==busy_time[i+1][1] ))){ // ПРОВЕРКА НА ЕДИНИЧНЫЕ ОТРЕЗКИ
            if(borders[0] & borders[1]){
                wwwork << busy_time[i][2] << busy_time[i][3]<<busy_time[i+1][0] <<busy_time[i+1][1];
                free_vec.insert(free_vec.end()-1,wwwork);
                wwwork.clear();
            }
            else if(borders[0]) {
                wwwork << busy_time[i][2] << busy_time[i][3]<<busy_time[i+1][0] <<busy_time[i+1][1];
                free_vec.push_back(wwwork);
                wwwork.clear();
            }
            else if(borders[1]){
                wwwork << busy_time[i][2] << busy_time[i][3]<<busy_time[i+1][0] <<busy_time[i+1][1];
                free_vec.insert(free_vec.end()-1,wwwork);
                wwwork.clear();
            }
            else{ // 4 условие
                wwwork << busy_time[i][2] << busy_time[i][3]<<busy_time[i+1][0] <<busy_time[i+1][1];
                free_vec.push_back(wwwork);
                wwwork.clear();
            }
        }
    }


    qDebug() << "ОКОНЧАТЕЛЬНЫЙ вывод после вставки всех элементов  ВЕКТОРА СВОБОДНОГО ВРЕМЕНИ" << free_vec;

    //можно сделать метод, который будет делать окончательные преобразования перед записью в БД - удалять элементы, у которых единичные отрезки
    // либо можно их сразу не записывать, проверяя условие - ПОПРОБУЮ пока это

    del = false;
    return flag;
}

void Time::setTimeBorders(int index, int a)
{
    timeBorders[index] = a;
}

void Time::set_borders_false()
{
    borders[0] = borders[1] = false;
}

void Time::setFree_vec_clear()
{
    free_vec.clear();

}

QVector<QVector<int> > Time::getBusy_time() const
{
    return busy_time;
}

void Time::setBusy_time_clear()
{
    busy_time.clear();
}

void Time::setClickable(bool ind) {
    isClickable = ind;
}

QVector<freedom> Time::getDistrubuted_time() const
{
    return distrubuted_time;
}

void Time::setDistrubuted_time(const QVector<freedom> &value)
{
    distrubuted_time = value;
}

QDate Time::getChosenDate() const
{
    return chosenDate;
}

void Time::setChosenDate(const QDate &value)
{
    chosenDate = value;
}

// ДОБАВЛЕННОЕ
void Time::paintEvent(QPaintEvent *event)
{
    lMarg = width()/14;
    upMarg = height()/8;

    QPainter painter(this);
    if (isClickable) painter.setBrush(QColor(240, 240, 240));
    else painter.setBrush(QColor(106, 177, 199));
    // Рисуем 2 поля для ввода:
    painter.drawRect(lMarg, upMarg,12*lMarg, 2*upMarg);
    painter.drawRect(lMarg, 5*upMarg,12*lMarg, 2*upMarg);
    int x(lMarg), y(upMarg);

    if (isClickable) {
        // Рисуем промежутки занятости
        for (int i=0; i<busy_time.size(); i++) {
            painter.setBrush(QColor(106, 177, 199));  // (52, 216, 0)
            int fromX = busy_time[i][0]*lMarg+lMarg+busy_time[i][1]*lMarg/60;
            int toX = busy_time[i][2]*lMarg+lMarg+busy_time[i][3]*lMarg/60;
            if (busy_time[i][0]>=12) {
                toX-=12*lMarg;
                fromX-=12*lMarg;
            }

            if (busy_time[i][0]<12) painter.drawRect(fromX, upMarg, toX-fromX, 2*upMarg);
            else painter.drawRect(fromX, 5*upMarg, toX-fromX, 2*upMarg);
            X1 = X2 = 0;
        }
    } else {

        // Рисуем промежутки распределенного времени
        for (int i=0; i<distrubuted_time.size(); i++) {
            if (getChosenDate() == distrubuted_time[i].getDate()) {
                painter.setBrush(QColor(106, 250, 100));  // (52, 216, 0)
                int fromX = distrubuted_time[i].getBeg_hour()*lMarg+lMarg+distrubuted_time[i].getBeg_minute()*lMarg/60;
                int toX = distrubuted_time[i].getEnd_hour()*lMarg+lMarg+distrubuted_time[i].getEnd_minute()*lMarg/60;
                if (distrubuted_time[i].getBeg_hour()>=12) {
                    toX-=12*lMarg;
                    fromX-=12*lMarg;
                }

                if (distrubuted_time[i].getBeg_hour()<12) painter.drawRect(fromX, upMarg, toX-fromX, 2*upMarg);
                else painter.drawRect(fromX, 5*upMarg, toX-fromX, 2*upMarg);
                X1 = X2 = 0;
            }
        }
    }

    // Рисуем шкалу
    for (int i=0; i<=12; i++) {
        y = upMarg;
        painter.drawLine(x, y, x, y+upMarg/4+3);
        painter.drawLine(x, y+2*upMarg, x, y+2*upMarg-upMarg/4-3);
        painter.drawText(x-13, y-20, 30, 20, Qt::AlignCenter, QString::number(i));

        y = 5*upMarg;
        painter.drawLine(x, y, x, y+upMarg/4+3);
        painter.drawLine(x, y+2*upMarg, x, y+2*upMarg-upMarg/4-3);
        painter.drawText(x-13, y-20, 30, 20, Qt::AlignCenter, QString::number(i+12));
        x+=lMarg;
    }
}

void Time::mousePressEvent(QMouseEvent *event)
{
    if(isClickable && event->pos().x() > lMarg && event->pos().x() <= width()-lMarg) {
        if (event->pos().y() >= upMarg && event->pos().y() <= 3*upMarg) X1 = event->pos().x();
        else if (event->pos().y() >= 5*upMarg && event->pos().y() <= 7*upMarg) X1 = event->pos().x()+12*lMarg;
    }
}




void Time::mouseReleaseEvent(QMouseEvent *event)
{
    if (!isClickable) return;
    // Хитрым образом сохраняем координаты точки отпуска
    if (event->pos().x() > width()-lMarg) X2 = width()-lMarg;
    else X2 = event->pos().x();
    if (event->pos().x() < lMarg) X2 = lMarg;

    if (event->pos().y() >= 5*upMarg && event->pos().y() <= 7*upMarg)
        X2 += 12*lMarg;

    // считаем концы промежука времени
        timeBorders[0] = (X1-lMarg)/lMarg;
        timeBorders[1] = ((X1-lMarg)%lMarg * 60)/lMarg;
        timeBorders[2] = (X2-lMarg)/lMarg;
        timeBorders[3] = ((X2-lMarg)%lMarg * 60)/lMarg;

    // проверка на то, чтобы левый конец промежутка был меньше правого
        if (timeBorders[0] > timeBorders[2]) {
            int temp = timeBorders[2];
            timeBorders[2] = timeBorders[0];
            timeBorders[0] = temp;

            temp = timeBorders[3];
            timeBorders[3] = timeBorders[1];
            timeBorders[1] = temp;
        }
        if (timeBorders[0] == timeBorders[2] && timeBorders[1] > timeBorders[3]){
            int temp = timeBorders[3];
            timeBorders[3] = timeBorders[1];
            timeBorders[1] = temp;
        }

        if ((timeBorders[2]==12||timeBorders[2]==24) && timeBorders[3]==1) timeBorders[3] = 0;

        if (timeBorders[0]==-1) return;

        if(timeBorders[2] == 24) {
            timeBorders[2] = 23;
            timeBorders[3] = 59;
        }
    // сортировка промежутков занятости и подсчет промежутков свободного времени
        free_time();
        qDebug() << "**********************";

        update();
}

/* 9 круг ада нашего кода:

   ((end_h < busy_time[i][2]) && (end_h > busy_time[i][0]))||//  конечный в промежутке
                    ((begin_h > busy_time[i][0]) && (begin_h < busy_time[i][2]) )|| // нача час в промежутке
                   ((end_h == /*begin_h ==*/ // busy_time[i][0]) && ( end_m > busy_time[i][1]) && (begin_h < busy_time[i][0] || (begin_h ==busy_time[i][0] && begin_m < busy_time[i][3] ))   )|| //в начале часа
                   // ((/*end_h ==*/ begin_h == busy_time[i][2]) && ( begin_m < busy_time[i][3]) && (end_h > busy_time[i][2] || (end_h == busy_time[i][2] && end_m >busy_time[i][1] )) )||
                    //(begin_h == busy_time[i][0] && ( begin_m > busy_time[i][1]) && end_h!=begin_h)|| //??????
                    //(end_h  == busy_time[i][2] && end_m < busy_time[i][3]  && end_h!=begin_h )||
                   // (begin_h >= busy_time[i][0] && end_h <= busy_time[i][2] && begin_h != end_h) //||
                   // (begin_h <= busy_time[i][0] && (end_h >= busy_time[i][2]) && begin_h != end_h)// ??????



//((end_h < busy_time[i][2]) && (end_h > busy_time[i][0]))<<//  конечный в промежутке
//                    ((begin_h > busy_time[i][0]) && (begin_h < busy_time[i][2]) )<<// нача час в промежутке
//                    ((end_h == /*begin_h ==*/ busy_time[i][0]) && ( end_m > busy_time[i][1]) && (begin_h < busy_time[i][0] || (begin_h ==busy_time[i][0] && begin_m < busy_time[i][3] ))   )<< //в начале часа
//                    ((/*end_h ==*/ begin_h == busy_time[i][2]) && ( begin_m < busy_time[i][3]) && (end_h > busy_time[i][2] || (end_h == busy_time[i][2] && end_m >busy_time[i][1] )) )<<
//                    (begin_h == busy_time[i][0] && ( begin_m > busy_time[i][1]))<<
//                    //(end_h  == busy_time[i][2] && end_m < busy_time[i][3])<<
//                    (begin_h >= busy_time[i][0] && end_h <= busy_time[i][2] && begin_h != end_h) <<
//                    //(begin_h <= busy_time[i][0] && (end_h >= busy_time[i][2]) && begin_h != end_h) <<
//                     " " << begin_h  << " " << begin_m<< " " << end_h<< " " <<end_m



////if(!((busy_time[i][2] == busy_time[i+1][0]) && (busy_time[i][3] ==busy_time[i+1][1] )))
//{
//    if(!free_vec.empty() && !del){
//        free_vec.insert(free_vec.end()-1,QVector<int>()); //ПРОБУЕММ end
//    }
//    else {
//        free_vec.push_back(QVector<int>());
//        del = true;
//    }
//   // qDebug() << "ПРоверка после вставки!! " << free_vec;
//    free_vec[i+k].push_back(busy_time[i][2]);
//     free_vec[i+k].push_back(busy_time[i][3]) ; // УБРАЛ +1
//    free_vec[i+k].push_back(busy_time[i+1][0]);
//    free_vec[i+k].push_back(busy_time[i+1][1]); //УБРАЛ -1
//}
