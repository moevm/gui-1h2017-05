#ifndef KEKNAIZER_H
#define KEKNAIZER_H

#include <QWidget>
#include <QTime>

#include <QMenu>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QGraphicsDropShadowEffect>
#include "time.h"
#include "problems.h"
#include "task.h"
#include "database.h"
#include "popup.h"

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

     void mouseMoveEvent(QMouseEvent* e);
     void mousePressEvent(QMouseEvent* e);
     void mouseReleaseEvent(QMouseEvent* e);
     void closeEvent(QCloseEvent * event);

     float dx;
     float dy;
private slots:
    void free_time();
    void qBox1(int a);
    void qBox2(int a);
    void qBox3(int a);
    void qBox4(int a);

    void on_problems_add();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

    void on_pushButton_4_clicked();

    //вывод текущих задач из БД
    void on_bd_task(QDate qd);


    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_pushButton_10_clicked();

private:
    Ui::keknaizer *ui;
    Time time;
    vector<task> to_do_list;
    problems *pr;
    DataBase kdb;
    QSystemTrayIcon  * trayIcon;
    PopUp *popUp;

};

#endif // KEKNAIZER_H
