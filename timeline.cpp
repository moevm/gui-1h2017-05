#include "timeline.h"

TimeLIne::TimeLIne(QWidget *parent) : QWidget(parent)
{
    //новое
    setMaximumSize(1000, 300);
    X1 = X2 = 0;
        lastIndex = -1;
        setWindowTitle(tr("Input time"));
        resize(1300, 200);
        lMarg = width()/26;
        upMarg = height()/4;
}

void TimeLIne::my_sort(QVector<QVector<int>> &a, int index)
{
    QVector<int> work_var(4);
    for (int i = 0; i < a.size()-1; i++){
        for (int j = i; j < a.size()-1/*-i*/; j++){
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


// ДОБАВЛЕННОЕ
void TimeLIne::paintEvent(QPaintEvent *event)
{
    lMarg = width()/26;
    upMarg = height()/4;

    QPainter painter(this);
    painter.setBrush(QColor(255, 255, 255));
    //painter.drawRect(50, 50, 1200, 100);
    painter.drawRect(lMarg, upMarg, 24*lMarg, 2*upMarg);
    int x(lMarg), y(upMarg);

    for (int i=0; i<=24; i++) {
        painter.drawLine(x, y, x, y+upMarg/4+3);
        painter.drawLine(x, y+2*upMarg, x, y+2*upMarg-upMarg/4-3);

        painter.drawText(x-13, y-20, 30, 20, Qt::AlignCenter, QString::number(i));
        x+=lMarg;
    }
    painter.setBrush(QColor(175, 218, 252, 200));
    for (int i=0; i<=lastIndex && i < 10; i++) {

        //painter.setBrush(QColor(159, 226, 191));
        //painter.setBrush(QColor(80, 200, 120));
        //painter.setBrush(QColor(255, 0, 51));
        int fromX = busy_time[i][0]*lMarg+lMarg+busy_time[i][1]*lMarg/60;
        int toX = busy_time[i][2]*lMarg+lMarg+busy_time[i][3]*lMarg/60;
        painter.drawRect(fromX, upMarg, toX-fromX, 2*upMarg);
        X1 = X2 = 0;
    }
}

void TimeLIne::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > lMarg && event->pos().x() <= width()-lMarg
            && event->pos().y() >= upMarg && event->pos().y() <= height()-upMarg)
    {
        X1 = event->pos().x();
    }
}

void TimeLIne::mouseReleaseEvent(QMouseEvent *event)
{
    if (X1 != 0 && event->pos().x()>= X1 && event->pos().x() >= lMarg)
    {
        if (event->pos().x() > width()-lMarg) X2 = width()-lMarg;
        else X2 = event->pos().x();

        lastIndex++;

        busy_time.push_back(QVector<int>());
        busy_time.last().push_back((X1-lMarg)/lMarg);
        busy_time.last().push_back(((X1-lMarg)%lMarg * 60)/lMarg);
        busy_time.last().push_back((X2-lMarg)/lMarg);
        busy_time.last().push_back(((X2-lMarg)%lMarg * 60)/lMarg);

        qDebug() << "Start hour: " << busy_time.last()[0];
        qDebug() << "Start minute: " << busy_time.last()[1];
        qDebug() << "End hour: " << busy_time.last()[2];
        qDebug() << "End minute: " << busy_time.last()[3];
        qDebug() << "**********************";


        for (int j(0); j<4;j++) my_sort(busy_time, j);

        update();
    }
}
