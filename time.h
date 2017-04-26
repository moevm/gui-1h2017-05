#ifndef TIME_H
#define TIME_H

#include <QMessageBox>
#include <QVector>

using namespace std;

class Time
{
public:
    Time();
    void my_sort(int (*a)[4], int index);
    bool free_time();
    void setTimeBorders(int index, int a);
    //int* getFreeTime() {return free[4];}
    int getNumbInterv() {return number_of_free_intvls;} //исправил на free
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
    int number_of_free_intvls =0;
    int work_var[4];
    bool left_border;
    bool right_border;



};

#endif // TIME_H
