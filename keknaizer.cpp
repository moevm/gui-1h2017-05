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

    popUp = new PopUp();

    //time = new Time();
    //ui->stackedWidget->addWidget(new Time());

//    QComboBox *my_combo = new QComboBox(QWidget *parent = 0);
//    QComboBox *combobox_2 = new QComboBox(QWidget *parent = 0);

    QStringList *mytext = new QStringList();
    for (int  i = 0; i < 24; i++){
        mytext->push_back("i");
    }

//    ui->comboBox_4->addItems(*mytext);
//    ui->comboBox_7->addItems(*mytext);
//    mytext->clear();
//    for(int j =0; j< 60; j++){
//        mytext->push_back("i");
//    }
//    ui->comboBox_6->addItems(*mytext);
//    ui->comboBox_8->addItems(*mytext);

    //прячем дерево задач
   // ui->treeWidget->hide();
    ui->pushButton_5->hide();   // Скрыли кнопку
    //это для крутоты
    ui->treeWidget->setAlternatingRowColors(true);
    ui->treeWidget->setAnimated(true);
    ui->treeWidget->setWordWrap(true);


   trayIcon = new QSystemTrayIcon(this);
   trayIcon->setIcon(QIcon(":/icon.png"));
   QMenu * menu = new QMenu(this);
   QAction * viewWindow = new QAction(trUtf8("Развернуть окно"), this);
   QAction * quitAction = new QAction(trUtf8("Выход"), this);


   connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
   connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

   menu->addAction(viewWindow);
   menu->addAction(quitAction);


   trayIcon->setContextMenu(menu);
   trayIcon->show();

   connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
           this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}

keknaizer::~keknaizer()
{
    delete ui;
}

void keknaizer::free_time()
{
    if (ui->time_widget->free_time()) {
//        for (int i = 0; i < time.getNumbInterv()-1; i++) {
//                       qDebug() << "C " << (time.getmyVec())[i][0] << " : " << (time.getmyVec())[i][1] << " до " << (time.getmyVec())[i][2] << " : " << (time.getmyVec())[i][3];
//        }
//    }

//        qDebug() << "-----------";
//        ui->plainTextEdit_2->clear();
//        for (int i = 0; i < time.getmyVec().size(); i++){//через функцию, УБРАЛ -1
//            ui->plainTextEdit_2->insertPlainText("C " + QString::number((time.getmyVec())[i][0]) + " : "  + QString::number((time.getmyVec())[i][1]) + " до " +  QString::number((time.getmyVec())[i][2]) +  " : "  + QString::number((time.getmyVec())[i][3]) + "\n" );
//        }
    }

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
    }
       // qDebug() << items.at(i) << " А ЗЕ ЗАЗ ЗА З";


//        for(int j =1; j<mytask[i].size()-1; j++){
//            items.append(new QTreeWidgetItem(items.at(i*(mytask[i].size()+1)), QStringList(mytask[i][j])));
//        }

    for(int i = 0; i <  mytask.size(); i++ ){
       items.append(new QTreeWidgetItem(items.at(i), QStringList("DEADLINE - " + mytask[i][1])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList(mytask[i][2])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList("Подробно:")));
       items.append(new QTreeWidgetItem(items.at(mytask.size()-1+(i+1)*mytask[i].size()-1), QStringList(mytask[i][3])));
       items.last()->setSizeHint(0,QSize(30,50)); //ИЗменение ширины строки, надо поиграться
       //items.last()->set
       //items.at(0)
    }

    ui->treeWidget->insertTopLevelItems(0, items);
    ui->treeWidget->setColumnWidth(0,40);
    ui->treeWidget->setWordWrap(true); //Разрешаем переносы
}

//Закрашивание дат календаря с дедлайнами
void keknaizer::on_my_tasks_tap()
{
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
       //items.last()->setSizeHint(1,QSize(10,10));


    //ui->treeWidget->insertTopLevelItems(0, items);

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


void keknaizer::mouseMoveEvent( QMouseEvent* e ) {
//    if( e->buttons() | Qt::LeftButton ) {
//        setGeometry(
//            pos().x() + ( e->x() - dx ),
//            pos().y() + ( e->y() - dy ),
//            width(),
//            height()
//        );
//    }
}

void keknaizer::mousePressEvent( QMouseEvent* e ) {
//    if( e->button() == Qt::LeftButton ) {
//        dx = e->x();
//        dy = e->y();
//        setCursor( Qt::OpenHandCursor );
//    }
}

void keknaizer::mouseReleaseEvent( QMouseEvent* e ) {
//    if( e->button() == Qt::LeftButton ) {
//        setCursor( Qt::ArrowCursor );
//    }
}

void keknaizer::on_pushButton_10_clicked()
{
    if (this->isMinimized()) {
        this->showNormal();
    } else {
        this->showMinimized();
    }
}

void keknaizer::cancel_time()
{
   ui->time_widget->setBusy_time_clear();
   ui->time_widget->setFree_vec_clear();
   ui->time_widget->set_borders_false();
   qDebug() << ui->time_widget->getBusy_time();
   qDebug() << ui->time_widget->getmyVec();

}

void keknaizer::closeEvent(QCloseEvent * event)
{
    /* Если окно видимо и чекбокс отмечен, то завершение приложения
     * игнорируется, а окно просто скрывается, что сопровождается
     * соответствующим всплывающим сообщением
     */
    if(this->isVisible()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        trayIcon->showMessage("Keknaizer",
                              trUtf8("Приложение свернуто в трей. Для того чтобы "
                                     "развернуть окно приложения, щелкните по иконке приложения в трее."),
                              icon,
                              2000);
    }
}

void keknaizer::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:

            /* если окно видимо, то оно скрывается,
             * и наоборот, если скрыто, то разворачивается на экран
             * */
            if(!this->isVisible()){
                this->show();
            } else {
                this->hide();
            }

        break;
    default:
        break;
    }
}

