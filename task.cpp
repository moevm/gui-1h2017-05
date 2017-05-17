#include "task.h"
#include <QDebug>

task::task():description(""),name(""),difficult(0)
{
    //qDebug() << deadline.currentDate();
}

task::~task()
{

}

QString task::getDescription() const
{
    return description;
}

void task::setDescription(const QString &value)
{
    description = value;
}

QString task::getName() const
{
    return name;
}

void task::setName(const QString &value)
{
    name = value;
}

unsigned int task::getDifficult() const
{
    return difficult;
}

void task::setDifficult(unsigned int value)
{
    difficult = value;
}

QDate task::getDeadline() const
{
    return deadline;
}

void task::setDeadline(const QDate &value)
{
    deadline = value;
}
