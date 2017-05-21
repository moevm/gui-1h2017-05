#include "keknaizer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    keknaizer w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setWindowIcon(QIcon(":/icon.png"));
    w.show();

    return a.exec();
}
