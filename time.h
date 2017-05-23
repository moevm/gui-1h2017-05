#ifndef TIME_H
#define TIME_H

#include <QMessageBox>
#include <QVector>
#include <QWidget>
#include <freedom.h>
#include <database.h>
#include <popup.h>

using namespace std;

class Time: public QWidget
{
    Q_OBJECT

public:
    Time(QWidget *parent = 0);
    void my_sort(QVector<QVector<int>> &a, int index);
    bool free_time();
    void setTimeBorders(int index, int a);
    //int* getFreeTime() {return free[4];}
    int getNumbInterv() {return busy_time.size();}
     QVector<QVector<int>> getmyVec(){return free_vec;}
     void setmyVec(const QVector<QVector<int>> &new_time);

     void setFree_vec_clear();

     QVector<QVector<int>> getBusy_time() const;
     void setBusy_time(const QVector<QVector<int>> &new_time);
     void setBusy_time_clear();  //clear
     void set_borders_false();
     void setClickable(bool ind);

     QVector<freedom> getDistributed_time() const;
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
        void paintEvent(QPaintEvent *event) override;

};

#endif // TIME_H
