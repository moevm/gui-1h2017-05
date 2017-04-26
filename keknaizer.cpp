#include "keknaizer.h"
#include "ui_keknaizer.h"
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

keknaizer::keknaizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keknaizer)
{
    ui->setupUi(this);

//    QComboBox *my_combo = new QComboBox(QWidget *parent = 0);
//    QComboBox *combobox_2 = new QComboBox(QWidget *parent = 0);

    QStringList *mytext = new QStringList();
    for (int  i = 0; i < 24; i++){
        mytext->push_back("i");
    }


    for (int  i = 0; i < 10; i++){
        {
            for (int  j = 0; j < 4; j++){
                busy_time[i][j] = -1;
            }
        }

    }

}

void keknaizer::my_sort(times &a,int index)
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

keknaizer::~keknaizer()
{
    delete ui;
}

void keknaizer::free_time()
{
    bool flag = true;
    if (number_of_intvls == 10){
        qDebug() << "Take it easy, maaan.";
        flag = false;
    }
    else if ((end_h < begin_h ) || ((begin_h == end_h) && (end_m <begin_m )) ){

        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Неверно введено время.");
        msg->show();
        flag = false;
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
            }
        }
    }
    if (flag){



        busy_time[number_of_intvls][0] = begin_h;
        busy_time[number_of_intvls][1] = begin_m;
        busy_time[number_of_intvls][2] = end_h;
        busy_time[number_of_intvls][3] = end_m;
        number_of_intvls++;

        for (int j = 0; j < 4; j++){
           my_sort(busy_time,j);
        }

        qDebug() << "Занято: ";
        for (int i = 0; i < number_of_intvls; i++) {
                           qDebug() << "C " << busy_time[i][0] << " : " << busy_time[i][1] << " до " << busy_time[i][2] << " : " << busy_time[i][3];
                   }

        qDebug() << "-----------";
        qDebug() << "Свободно: ";

        times free;

        for(int i = 0; i < number_of_intvls-1; i++){
            free[i][0] = busy_time[i][2]; //час
            free[i][1] = busy_time[i][3] +1; // минуты
            if (free[i][1]%60 == 0){ // если было 59
                free[i][1] = 0;
                free[i][0]++;
            }

            free[i][2] = busy_time[i+1][0];
            free[i][3] = busy_time[i+1][1]-1;
            if(free[i][3] < 0){
                free[i][3] +=60;
                free[i][2]--;
            }
        }


            for (int i = 0; i < number_of_intvls-1; i++) {
                           qDebug() << "C " << free[i][0] << " : " << free[i][1] << " до " << free[i][2] << " : " << free[i][3];

                   }

         qDebug() << "-----------";

        // int *suka = max_huesos();



            for (int i = 0; i < number_of_intvls-1; i++){
        ui->plainTextEdit_2->insertPlainText("C " + QString::number(free[i][0]) + " : "  + QString::number(free[i][1]) + " до " +  QString::number(free[i][2]) +  " : "  + QString::number(free[i][3]) + "\n" );
}

}
}

//int& max_huesos() {return (*free)[4];}

void keknaizer::qBox1(int a)
{
    begin_h = a;

}

void keknaizer::qBox2(int a)
{
    begin_m = a;

}

void keknaizer::qBox3(int a)
{
    end_h = a;
}

void keknaizer::qBox4(int a)
{
    end_m = a;

}


void keknaizer::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void keknaizer::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void keknaizer::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
