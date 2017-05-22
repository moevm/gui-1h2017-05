#ifndef FREEDOM_H
#define FREEDOM_H

#include <QDate>

class freedom
{
public:
    freedom();
    ~freedom();

    QDate getDate() const;
    void setDate(const QDate &value);

    int getBeg_hour() const;
    void setBeg_hour(int value);

    int getBeg_minute() const;
    void setBeg_minute(int value);

    int getEnd_hour() const;
    void setEnd_hour(int value);

    int getEnd_minute() const;
    void setEnd_minute(int value);

    QString getTask_name() const;
    void setTask_name(const QString &value);

private:

    QDate date;
    int beg_hour;
    int beg_minute;
    int end_hour;
    int end_minute;
    QString task_name;

};

#endif // FREEDOM_H
