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
    //time = new Time();
    //ui->stackedWidget->addWidget(new Time());

//    QComboBox *my_combo = new QComboBox(QWidget *parent = 0);
//    QComboBox *combobox_2 = new QComboBox(QWidget *parent = 0);

    QStringList *mytext = new QStringList();
    for (int  i = 0; i < 24; i++){
        mytext->push_back("i");
    }

}

keknaizer::~keknaizer()
{
    delete ui;
}

void keknaizer::free_time()
{
    if (time.free_time()) {
//        for (int i = 0; i < time.getNumbInterv()-1; i++) {
//                       qDebug() << "C " << (time.getmyVec())[i][0] << " : " << (time.getmyVec())[i][1] << " до " << (time.getmyVec())[i][2] << " : " << (time.getmyVec())[i][3];
//        }
//    }

//        qDebug() << "-----------";
        ui->plainTextEdit_2->clear();
        for (int i = 0; i < time.getNumbInterv()-1; i++){//через функцию
            ui->plainTextEdit_2->insertPlainText("C " + QString::number((time.getmyVec())[i][0]) + " : "  + QString::number((time.getmyVec())[i][1]) + " до " +  QString::number((time.getmyVec())[i][2]) +  " : "  + QString::number((time.getmyVec())[i][3]) + "\n" );
        }
    }

}

void keknaizer::qBox1(int a)
{
    time.setTimeBorders(0, a);
}

void keknaizer::qBox2(int a)
{
    time.setTimeBorders(1, a);
}

void keknaizer::qBox3(int a)
{
    time.setTimeBorders(2, a);
}

void keknaizer::qBox4(int a)
{
    time.setTimeBorders(3, a);
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

void keknaizer::on_problems_add()
{
    if((ui->plainTextEdit_3->toPlainText() != "") && (ui->plainTextEdit_4->toPlainText() != ""))
    {
        if(ui->calendarWidget->selectedDate() < QDate::currentDate())
        {
            QMessageBox *msg = new QMessageBox(NULL);
            msg->setText("Дедлайн ващй задачи некорректен");
            msg->show();
        }
        else
        {
            task cur_task ;
            cur_task.setDeadline(ui->calendarWidget->selectedDate());
            cur_task.setDescription(ui->plainTextEdit_3->toPlainText());
            ui->plainTextEdit_3->clear();
            cur_task.setName(ui->plainTextEdit_4->toPlainText());
            ui->plainTextEdit_4->clear();
            cur_task.setDifficult(ui->comboBox_9->currentIndex());

            to_do_list.push_back(cur_task) ;

           // (to_do_list.at(0)).getName();
            qDebug() << to_do_list.at(0).getDeadline().toString("dd/MM/yy");
        }
    }
    else {
        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Не все данные были введены");
        msg->show();
    }
}

