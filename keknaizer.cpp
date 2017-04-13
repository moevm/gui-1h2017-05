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
        ui->plainTextEdit->clear();
        for (int i = 0; i < time.getNumbInterv()-1; i++){//через функцию
            ui->plainTextEdit->insertPlainText("C " + QString::number((time.getmyVec())[i][0]) + " : "  + QString::number((time.getmyVec())[i][1]) + " до " +  QString::number((time.getmyVec())[i][2]) +  " : "  + QString::number((time.getmyVec())[i][3]) + "\n" );
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

