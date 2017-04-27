#ifndef TIME_H
#define TIME_H

#include <QMessageBox>
#include <QVector>
#include <QWidget>

using namespace std;

class Time: public QWidget
{
public:
    Time(QWidget *parent = 0);
    void my_sort(int (*a)[4], int index);
    bool free_time();
    void setTimeBorders(int index, int a);
    //int* getFreeTime() {return free[4];}
    int getNumbInterv() {return number_of_intvls;}
    vector<vector<int>> getmyVec(){return free_vec;}

private:
    int timeBorders[4];
    vector<vector<int>> free_vec;
    //int free[10][4];    // массив свободного времени


//    int begin_h =0;
//    int begin_m =0;
//    int end_h =0;
//    int end_m =0;
    int busy_time[10][4];
    int number_of_intvls =0;
    int work_var[4];

    // измененное
        int X1, X2; // координаты отрезка для отрисовки
        int lMarg, upMarg; // переменные для правильной отрисовки линии в любом размере
        int lastIndex;  // индекс последнего доступного в массиве интервала

    protected:
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);



};

#endif // TIME_H
