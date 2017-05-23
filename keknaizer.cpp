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


    //прячем дерево задач
    ui->pushButton_5->hide();   // Скрыли кнопку
    //это для крутоты
    ui->treeWidget->setAlternatingRowColors(true);
    ui->treeWidget->setAnimated(true);
    ui->treeWidget->setWordWrap(true);

    ui->time_widget->setClickable(true);
    ui->time_widget_2->setClickable(false);

    //инициализация pushbutto_11
    ui->pushButton_11->setText(ui->calendarWidget_3->selectedDate().toString());


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

   time_algorithm();


}

keknaizer::~keknaizer()
{
    delete ui;
}

void keknaizer::free_time()
{
    ui->time_widget->free_time();
//    ui->time_widget->lines();
    // Добавить проверку?

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
    ui->treeWidget->setColumnCount(1);

    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < mytask.size(); i++){
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(mytask[i][0])));
    }

    for(int i = 0; i <  mytask.size(); i++ ){
       items.append(new QTreeWidgetItem(items.at(i), QStringList("DEADLINE - " + mytask[i][1])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList(mytask[i][2])));
       items.append(new QTreeWidgetItem(items.at(i), QStringList("Подробно:")));
       items.append(new QTreeWidgetItem(items.at(mytask.size()-1+(i+1)*mytask[i].size()-1), QStringList(mytask[i][3])));
       items.last()->setSizeHint(0,QSize(30,50)); //ИЗменение ширины строки, надо поиграться
    }

    ui->treeWidget->insertTopLevelItems(0, items);
    ui->treeWidget->setColumnWidth(0,40);
    ui->treeWidget->setWordWrap(true); //Разрешаем переносы


    // Обновляем дату для линии времени
    ui->time_widget_2->setChosenDate(ui->calendarWidget_2->selectedDate());
    ui->time_widget_2->setmyVec(kdb.get_free_user_time(ui->time_widget_2->getChosenDate()));
    ui->time_widget_2->repaint();
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

     // Обновляем линию времени
     updateDistrLine(); //
     ui->time_widget_2->setChosenDate(ui->calendarWidget_2->selectedDate());
     ui->time_widget_2->setmyVec(kdb.get_free_user_time(ui->time_widget_2->getChosenDate()));
     ui->time_widget_2->repaint();

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

            time_algorithm();
        }
    }
    else {
        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Не все данные были введены");
        msg->show();
    }
}


void keknaizer::mouseMoveEvent( QMouseEvent* e ) {
   if ((abs(width() - dx) < width()/15 || width() + dx < width()+width()/25)
           ||(abs(height() - dy) < height()/25 || height() + dy < height()+height()/20))
   {
    if( e->buttons() | Qt::LeftButton ) {
        if (dx == 0 && dy == 0) {
        setGeometry(
            pos().x(),
            pos().y(),
            width(),
            height()
         );
        }
        else  {
            setCursor( Qt::OpenHandCursor);
            setGeometry(
                pos().x() + ( e->x() - dx ),
                pos().y() + ( e->y() - dy ),
                width(),
                height()
             );
            }
     }
   }
}

void keknaizer::mousePressEvent( QMouseEvent* e ) {
    if(e->button() == Qt::LeftButton) {
        dx = e->x();        //Границы : dx = 200 , dy = 40; dx = 860 , dy = 40; dx = 200 , dy = 710; dx = 860 , dy = 710;
        dy = e->y();
    }
}

void keknaizer::mouseReleaseEvent( QMouseEvent* e ) {
    if( e->button() == Qt::LeftButton ) {
        setCursor( Qt::ArrowCursor );
        dx=0;
        dy=0;
    }
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

void keknaizer::add_freedom()
{

    QVector<QVector<int>> work_freedom = ui->time_widget->getmyVec();
    ui->time_widget_2->setBusy_time(ui->time_widget->getBusy_time());

    if(work_freedom.empty())
    {
        QMessageBox *msg = new QMessageBox(NULL);
        msg->setText("Введите свое занятое время");
        msg->show();
    } else if(QDate::fromString(ui->pushButton_11->text(),"ddd MMM dd yyyy") >
              QDate::fromString(ui->pushButton_12->text(), "ddd MMM dd yyyy")) {
            QMessageBox *msg = new QMessageBox(NULL);
            msg->setText("Неверно введены даты занятости");
            msg->show();

    } else{
        kdb.delete_same_dates(QDate::fromString(ui->pushButton_11->text(),"ddd MMM dd yyyy"),
                              QDate::fromString(ui->pushButton_12->text(), "ddd MMM dd yyyy"),
                              kdb.get_free_dates());
        kdb.add_free_user_time(QDate::fromString(ui->pushButton_11->text(),"ddd MMM dd yyyy"),
                               work_freedom,
                               QDate::fromString(ui->pushButton_12->text(),"ddd MMM dd yyyy"));
        // Запускаем алгоритм расчета времени
        ui->time_widget_2->setDistrubuted_time(time_algorithm());
        emit ui->pushButton_6->clicked();
    }

}

void keknaizer::update_dates()
{

    if(!ui->pushButton_11->isChecked() == true){
        ui->pushButton_11->setText(ui->calendarWidget_3->selectedDate().toString());
    }else{
        ui->pushButton_12->setText(ui->calendarWidget_3->selectedDate().toString());
    }
}

void keknaizer::try_change_color()
{
    if(sender()==ui->pushButton_11){
        ui->pushButton_11->setStyleSheet("QPushButton#pushButton_11 {"
                                         "padding: 1px 2px;"
                                         "font: normal 14px Roboto;"
                                         "border: none;"
                                         "color: rgb(55, 125, 255);"
                                         "background-color: none;"
                                         "text-align: center;"
                                         "border-bottom: 3px solid rgb(25, 170, 0);"
                                         "font-family: Roboto,Helvetica Neue Light,Helvetica Neue,Helvetica,Arial,sans-serif;}"
                                         "QPushButton#pushButton_11:hover {"
                                         "color: #fff;"
                                         "border: 3px solid rgb(25, 170, 0);}");
       ui->pushButton_11->setChecked(false);
       ui->pushButton_12->setChecked(true);
       ui->pushButton_12->setStyleSheet("QPushButton#pushButton_12 {"
                                        "padding: 1px 2px;"
                                        "font: normal 14px Roboto;"
                                        "border: none;"
                                        "color: rgb(244, 16, 69);"
                                        "background-color: none;"
                                        "text-align: center;"
                                        "border-bottom: 3px solid rgb(255, 170, 0);"
                                        "font-family: Roboto,Helvetica Neue Light,Helvetica Neue,Helvetica,Arial,sans-serif;}"
                                        "QPushButton#pushButton_11:hover {"
                                        "color: #fff;"
                                        "border: 3px solid rgb(255, 170, 0);}");
    }
    else{
        ui->pushButton_12->setStyleSheet("QPushButton#pushButton_12 {"
                                         "padding: 1px 2px;"
                                         "font: normal 14px Roboto;"
                                         "border: none;"
                                         "color: rgb(55, 125, 255);"
                                         "background-color: none;"
                                         "text-align: center;"
                                         "border-bottom: 3px solid rgb(25, 170, 0);"
                                         "font-family: Roboto,Helvetica Neue Light,Helvetica Neue,Helvetica,Arial,sans-serif;}"
                                         "QPushButton#pushButton_12:hover {"
                                         "color: #fff;"
                                         "border: 3px solid rgb(25, 170, 0);}");
        ui->pushButton_12->setChecked(false);
        ui->pushButton_11->setChecked(true);
        ui->pushButton_11->setStyleSheet("QPushButton#pushButton_11 {"
                                         "padding: 1px 2px;"
                                         "font: normal 14px Roboto;"
                                         "border: none;"
                                         "color: rgb(244, 16, 69);"
                                         "background-color: none;"
                                         "text-align: center;"
                                         "border-bottom: 3px solid rgb(255, 170, 0);"
                                         "font-family: Roboto,Helvetica Neue Light,Helvetica Neue,Helvetica,Arial,sans-serif;}"
                                         "QPushButton#pushButton_11:hover {"
                                         "color: #fff;"
                                         "border: 3px solid rgb(255, 170, 0);}");
    }
}

void keknaizer::updateDistrLine()
{
    ui->time_widget_2->setDistrubuted_time(kdb.get_all_dis_time());
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

QVector<freedom> keknaizer::time_algorithm() { // СДЕЛАТЬ ПРОВЕРКУ НА ПРОСРОЧЕННЫЕ ДЕДЛАЙНЫ

    QVector<freedom> distributedTime;   // вектор распределенного времени пользователя

    // подготавливаем массив свободного времени пользователя
        // назначаем текущим временем миг + 5 минут
        QTime curTime = QTime::currentTime();
        QDate curDate = QDate::currentDate();
        if (curTime > curTime.addSecs(300)) curDate = curDate.addDays(1);
        curTime = curTime.addSecs(300);

        //считываем базу данных свободного времени
        QVector<freedom> free_vec = kdb.all_free_times();

        //считываем базу данных задач пользователя
        QVector<task> task_list = kdb.get_all_tasks_by_date_and_diff();

        // Ищем индекс промежутка, в который попадает текущее время
        int index = 0;
        int vecSize = free_vec.size();
        for (index; index < vecSize; index++) {     // Индекс ищется
            if (curDate <= free_vec[index].getDate()) {
                int left = QTime(free_vec[index].getBeg_hour(), free_vec[index].getBeg_minute()).secsTo(QTime(curTime.hour(), curTime.minute()))/60;
                int right = QTime(curTime.hour(), curTime.minute()).secsTo(QTime(free_vec[index].getEnd_hour(), free_vec[index].getEnd_minute()))/60;


                if (left >=0) {
                    if (right > 0) {
                        free_vec[index].setBeg_hour(curTime.hour());
                        free_vec[index].setBeg_minute(curTime.minute());
                        break;
                    }
                } else break; //хат фекс 228,5
            }
        };

        // проверка на всякий пожарный (А может ли к этому моменту закончиться свободное время?)
        if (index == vecSize) {
            qDebug() << "Zabil dobafit svobodniy vryemia || Свободное время закончилось";
            QMessageBox *msg = new QMessageBox(NULL);
            msg->setText("Пересмотрите план вашей занятости - у вас совсем нет свободного времени!");
            msg->show();
            kdb.delete_and_insert_in_dis_time(distributedTime);
            return distributedTime;
        }
        // убрали из массива свободного времени то время, которое пользователь уже не может использовать
        if (index) {
            free_vec.remove(0, index); // Может быть заменить на сдвиг?
            index = 0;
            vecSize = free_vec.size();
        }

        // сложность рассматриваемой задачи
        int taskVolume(0);

    while (!task_list.isEmpty()) {

        // рассматриваемый deadline на текущем шаге
        QDate curDeadline = task_list.first().getDeadline();

        // Считаем кол-во задач для текущего дедлайна
        QDate temp;
        int curTaskNumb(0);
        temp = curDeadline;

        while(temp == curDeadline && curTaskNumb!=task_list.size() ){

            temp = task_list[curTaskNumb].getDeadline(); // здесь нагнулся
            curTaskNumb++;
        }

        for (int i = 0; i < curTaskNumb; i++) {

            taskVolume = 0;  // объем задачи в часах
            // определяем коэффициент сложности задачи
            switch (task_list[i].getDifficult()) {
                case 0:
                    taskVolume = 1;
                    break;
                case 1:
                    taskVolume = 2;
                    break;
                case 2:
                    taskVolume = 4;
                    break;
                case 3:
                    taskVolume = 8;
                    break;
                case 4:
                    taskVolume = 16;
                    break;
                default:
                    taskVolume = task_list[i].getDifficult();   // пользовательский тип сложности
                    qDebug() << "Warning: unknown type of task difficulty.";
            }
            taskVolume *= 60;   // Перевели объем задачи в минуты
            taskVolume += taskVolume/(1.51*6);     // ДОБАВИТЬ ПОЛЬЗОВАТЕЛЮ НАПОМИНАНИЯ О ТОМ, ЧТОБЫ ЧЕРЕЗ КАЖДЫЕ 1.5 часа ОН ДЕЛАЛ ПЕРЕРЫВ на 15 мин. NB
            taskVolume += 15;   // добавили 15 минут на перерыв между делами


            // Выделение времени в нужном объеме

                // Распределяем время на задачу
                while (taskVolume > 0) {
                    free_vec[index].setTask_name(task_list[i].getName());

                    int len = QTime(free_vec[index].getBeg_hour(),free_vec[index].getBeg_minute()).secsTo(QTime(free_vec[index].getEnd_hour(),free_vec[index].getEnd_minute()))/60;
                    // оставшееся время больше длины текущего промежутка?

                    if (len <= taskVolume) {

                        taskVolume -= len;
                        distributedTime.append(free_vec[index]);   //Продумать это место - удаление первого элемента из фриивек лолкекякутузбек

                        if (++index == vecSize) {   // Переделать условие - т.к. времени может хватить тютелька в тютельку
                            qDebug() << "Закончилось свободное время";
                            qDebug() << "Cвободное время:";
                            for(int i = 0; i < free_vec.size(); i++){
                                qDebug() << free_vec[i].getDate() << free_vec[i].getBeg_hour() <<free_vec[i].getBeg_minute() <<free_vec[i].getEnd_hour() <<free_vec[i].getEnd_minute() ;
                            }
                            qDebug() << "Распределенное время:";
                            for(int i = 0; i < distributedTime.size(); i++){
                                qDebug() << distributedTime[i].getDate() << distributedTime[i].getBeg_hour() <<distributedTime[i].getBeg_minute() <<distributedTime[i].getEnd_hour() <<distributedTime[i].getEnd_minute() ;
                            }

                            free_vec.remove(0, index);  // Кажется, именно столько
                            kdb.delete_and_insert_in_dis_time(distributedTime);

                            QMessageBox *msg = new QMessageBox(NULL);
                            msg->setText("Рекомендуем вам пересмотреть свои планы - вероятнее всего вам не хватит времени! ");
                            msg->show();

                            return distributedTime;
                        }

                    } else {

                        // добавляем в новый элемент вектора распределенного времени левый конец промежутка свободного времени
                        distributedTime.append(freedom());
                        distributedTime.last().setBeg_hour(free_vec[index].getBeg_hour());
                        distributedTime.last().setBeg_minute(free_vec[index].getBeg_minute());
                        // посчитаем правый промежуток для распределенного времени
                        QTime adjoint(free_vec[index].getBeg_hour(),free_vec[index].getBeg_minute());
                        adjoint = adjoint.addSecs((taskVolume)*60); // ДОБАВИТЬ перерыв на 15 минут между разными делами

                        free_vec[index].setBeg_hour(adjoint.hour());
                        free_vec[index].setBeg_minute(adjoint.minute());
                        // добавим в вектор распределенного времени правый конец промежутка
                        distributedTime.last().setEnd_hour(adjoint.hour());
                        distributedTime.last().setEnd_minute(adjoint.minute());
                        distributedTime.last().setDate(free_vec[index].getDate());
                        distributedTime.last().setTask_name(free_vec[index].getTask_name());

                        taskVolume = -1;    // заодно и индикатор
                    }
                } // закончили распределять время на текущую задачу

        }

        // Уберем из списка задач curTaskNumb задач, для которых мы уже распределили время


        task_list.remove(0, curTaskNumb);

    }// закончили распределять время для всех задач из списка

    // убираем из вектора свободного времени те промежутки, которые уже распределили
    free_vec.remove(0, index);  // Кажется, именно столько

    qDebug() << "Обычный конец работы алгоритма - свободное время:";
    for(int i = 0; i < free_vec.size(); i++){
        qDebug() << free_vec[i].getDate() << free_vec[i].getBeg_hour() <<free_vec[i].getBeg_minute() <<free_vec[i].getEnd_hour() <<free_vec[i].getEnd_minute() ;
    }
    qDebug() << "Распределенное время:";
    for(int i = 0; i < distributedTime.size(); i++){
        qDebug() << distributedTime[i].getDate() << distributedTime[i].getBeg_hour() <<distributedTime[i].getBeg_minute() <<distributedTime[i].getEnd_hour() <<distributedTime[i].getEnd_minute() ;
    }

    qDebug() << "Clear and paste new free distributed time? - " <<kdb.delete_and_insert_in_dis_time(distributedTime);
    return distributedTime;
}

