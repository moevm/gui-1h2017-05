#include "keknaizer.h"
#include "ui_keknaizer.h"
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QDate>

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

    //прячем дерево задач
    ui->treeWidget->hide();

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


//вот эта функция
void keknaizer::on_bd_task(QDate qd) //проверить
{
    ui->treeWidget->clear();

    QVector<QVector<QString>> mytask = kdb.cur_tasks(qd);
    if(mytask.size() != 0){
        for(int i =0; i < mytask.size(); i++){
            for(int j = 0; j<4; j++){
                 qDebug() << mytask[i][j];
            }

        }
    }

    QVector<QString> unique_dates = kdb.all_deadlines();

    //пытаемся закрасить ячейку календарика
     QTextCharFormat format;
     QBrush brush;
     QColor color;
     int r=200,g=145,b=234,a=120;
     color.setRgb(r,g,b,a);;
     brush.setColor(color);
     format.setBackground(brush);

     for(int i =0; i< unique_dates.size();i++){
          QDate date = QDate::fromString(unique_dates.at(i),"yyyy-MM-dd");
          ui->calendarWidget_2->setDateTextFormat(date,format);
     }

    //выводим дерево задач с заданным дедлайном
    ui->treeWidget->show();
    //ui->treeWidget->setHeaderLabel(new QLabel(this,"ЛОЛ КЕК ЧЕБУРЕК"));
    ui->treeWidget->setColumnCount(1);
    //ui->treeWidget->set

    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < mytask.size(); i++){
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(mytask[i][0])));
       // qDebug() << items.at(i) << " А ЗЕ ЗАЗ ЗА З";
    }

//        for(int j =1; j<mytask[i].size()-1; j++){
//            items.append(new QTreeWidgetItem(items.at(i*(mytask[i].size()+1)), QStringList(mytask[i][j])));
//        }
    for(int i = 0; i <  mytask.size(); i++ ){
       items.append(new QTreeWidgetItem(items.at(i), QStringList("DEADLINE - " + mytask[i][1])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList(mytask[i][2])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList("Подробно:")));
       items.append(new QTreeWidgetItem(items.at(mytask.size()-1+(i+1)*mytask[i].size()-1), QStringList(mytask[i][3])));
       //items.last()->setSizeHint(1,QSize(10,10));
    }

    ui->treeWidget->insertTopLevelItems(0, items);

    //delete items[];

     //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
}

void keknaizer::on_problems_add()
{
    if((ui->plainTextEdit_3->toPlainText() != "") && (ui->plainTextEdit_4->toPlainText() != ""))
    {
        if(ui->calendarWidget->selectedDate() < QDate::currentDate())
        {
            QMessageBox *msg = new QMessageBox(NULL);
            msg->setText("Дедлайн вашей задачи некорректен");
            msg->show();
        }
        else
        {
//            task cur_task ;
//            cur_task.setDeadline(ui->calendarWidget->selectedDate());
//            cur_task.setDescription(ui->plainTextEdit_3->toPlainText());
//            ui->plainTextEdit_3->clear();
//            cur_task.setName(ui->plainTextEdit_4->toPlainText());
//            ui->plainTextEdit_4->clear();
//            cur_task.setDifficult(ui->comboBox_9->currentIndex());

//            to_do_list.push_back(cur_task) ;

//           // (to_do_list.at(0)).getName();
//            qDebug() << to_do_list.at(0).getDeadline().toString("dd/MM/yy");

            //УБРАТЬ ВЫШЕ И ДОБАВИТ БД
            qDebug() << kdb.addTask((QString)(ui->plainTextEdit_4->toPlainText()),(QDate)ui->calendarWidget->selectedDate(),
                        ui->comboBox_9->currentIndex(),(QString)(ui->plainTextEdit_3->toPlainText()),QDate::currentDate());

            ui->plainTextEdit_3->clear();
            ui->plainTextEdit_4->clear();

        }
    }
    else {
        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Не все данные были введены");
        msg->show();
    }
}
