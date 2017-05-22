#ifndef TIME_H
#define TIME_H

#include <QMessageBox>
#include <QVector>
#include <QWidget>
#include <freedom.h>
#include <database.h>

using namespace std;

class Time: public QWidget
{
public:
    Time(QWidget *parent = 0);
    void my_sort(QVector<QVector<int>> &a, int index);
    bool free_time();
    void setTimeBorders(int index, int a);
    //int* getFreeTime() {return free[4];}
    int getNumbInterv() {return busy_time.size();}
     QVector<QVector<int>> getmyVec(){return free_vec;}

     void setFree_vec_clear();

     QVector<QVector<int> > getBusy_time() const;
     void setBusy_time_clear();  //clear
     void paintEvent(QPaintEvent *event) override;
     void set_borders_false();
     void setClickable(bool ind);

     QVector<freedom> getDistrubuted_time() const;
     void setDistrubuted_time(const QVector<freedom> &value);

     QDate getChosenDate() const;
     void setChosenDate(const QDate &value);

private:
     int timeBorders[4];
     QVector<QVector<int>> free_vec;
     bool borders[2];
     QVector<QVector<int>> busy_time;
     QVector<freedom> distrubuted_time;
     bool isClickable;
     QDate chosenDate;

    // измененное
        int X1, X2; // координаты отрезка для отрисовки
        int lMarg, upMarg; // переменные для правильной отрисовки линии в любом размере

    protected:

        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);



};

#endif // TIME_H
