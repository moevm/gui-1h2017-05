#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDate>

class task
{
public:
    task();
    ~task();

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    unsigned int getDifficult() const;
    void setDifficult(unsigned int value);

    QDate getDeadline() const;
    void setDeadline(const QDate &value);

private:
    QString description; // подробное описание
    QString name; // название
    unsigned int difficult; // сложность
    QDate deadline; // срок дедлайна
};

#endif // TASK_H
