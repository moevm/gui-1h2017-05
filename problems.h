#ifndef PROBLEMS_H
#define PROBLEMS_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QCalendarWidget>
class problems : public QWidget
{
    Q_OBJECT
public:
    explicit problems(QWidget *parent = 0);
private:
    QPlainTextEdit *for_name,*for_des;
    QComboBox *for_difficult;
    QPushButton *for_adding;
    QCalendarWidget *for_deadlines;
signals:

public slots:
};

#endif // PROBLEMS_H
