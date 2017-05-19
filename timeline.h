#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

using namespace std;

class TimeLIne : public QWidget
{
    Q_OBJECT

public:
    explicit TimeLIne(QWidget *parent = 0);

private:
    int X1, X2; // координаты отрезка для отрисовки
    int lMarg, upMarg; // переменные для правильной отрисовки линии в любом размере
    int lastIndex;  // индекс последнего доступного в массиве интервала

    QVector<QVector<int>> busy_time;

    void my_sort(QVector<QVector<int>> &a, int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // TIMELINE_H
