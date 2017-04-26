#include "keknaizer.h"
#include <QApplication>
#include <QDebug>
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    keknaizer w;
    w.show();

    return a.exec();

}
