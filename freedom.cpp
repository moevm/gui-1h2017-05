#include "freedom.h"

freedom::freedom()
{

}

freedom::~freedom()
{

}

QDate freedom::getDate() const
{
    return date;
}

void freedom::setDate(const QDate &value)
{
    date = value;
}

int freedom::getBeg_hour() const
{
    return beg_hour;
}

void freedom::setBeg_hour(int value)
{
    beg_hour = value;
}

int freedom::getBeg_minute() const
{
    return beg_minute;
}

void freedom::setBeg_minute(int value)
{
    beg_minute = value;
}

int freedom::getEnd_hour() const
{
    return end_hour;
}

void freedom::setEnd_hour(int value)
{
    end_hour = value;
}

int freedom::getEnd_minute() const
{
    return end_minute;
}

void freedom::setEnd_minute(int value)
{
    end_minute = value;
}

QString freedom::getTask_name() const
{
    return task_name;
}

void freedom::setTask_name(const QString &value)
{
    task_name = value;
}
