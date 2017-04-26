#ifndef KEKNAIZER_H
#define KEKNAIZER_H

#include <QWidget>
#include <QTime>

using namespace std;

namespace Ui {
class keknaizer;
}

class keknaizer : public QWidget
{
    Q_OBJECT

public:
    typedef int times[10][4];

    explicit keknaizer(QWidget *parent = 0);
    void my_sort( times &a, int index);
    //int max_huesos()[4] {return  &free[4];}
    ~keknaizer();

private slots:
    void free_time();

    void qBox1(int a);
    void qBox2(int a);
    void qBox3(int a);
    void qBox4(int a);
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::keknaizer *ui;
//    QTime begin_tm = new QTime();
//    QTime end_tm = new QTime();
    int begin_h =0;
    int begin_m =0;
    int end_h =0;
    int end_m =0;
    int busy_time[10][4] = {};
    int number_of_intvls =0;
    int work_var[4] = {};
};

#endif // KEKNAIZER_H
