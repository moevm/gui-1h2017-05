#ifndef KEKNAIZER_H
#define KEKNAIZER_H

#include <QWidget>
#include <QTime>
#include "kektime.h"
#include "task.h"
#include "database.h"

#include <QMenu>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QGraphicsDropShadowEffect>
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

    void on_problems_add();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    //вывод текущих задач из БД
    void on_bd_task(QDate qd);

    //по нажатию на "мои задачи"
    void on_my_tasks_tap();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_pushButton_10_clicked();
    //типо вот добовляем сейщас навцй слат
    void cancel_time();
    //добавить свободное время в БД
    void add_freedom();

    //обновление текущей и конечной даты
    void update_dates();

    void try_change_color();

    void updateDistrLine();


private:
    QVector<freedom> time_algorithm();  // Алгоритм распределения времени

    Ui::keknaizer *ui;
    //Time time;
    vector<task> to_do_list;
    DataBase kdb;

    QSystemTrayIcon  * trayIcon;
    PopUp *popUp;

};

#endif // KEKNAIZER_H
