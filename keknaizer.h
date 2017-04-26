#ifndef KEKNAIZER_H
#define KEKNAIZER_H

#include <QWidget>
#include <QTime>
#include "time.h"

using namespace std;

namespace Ui {
class keknaizer;
}

class keknaizer : public QWidget
{
    Q_OBJECT

public:


    explicit keknaizer(QWidget *parent = 0);

    ~keknaizer();

private slots:
    void free_time();
    void qBox1(int a);
    void qBox2(int a);
    void qBox3(int a);
    void qBox4(int a);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::keknaizer *ui;
    Time time;

};

#endif // KEKNAIZER_H
