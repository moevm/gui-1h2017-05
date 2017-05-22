#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T15:50:01
#
#-------------------------------------------------

QT       += core gui sql widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_GUIGUIGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        keknaizer.cpp \
    time.cpp \
    task.cpp \
    problems.cpp \
    database.cpp \
    timeline.cpp \
    popup.cpp \
    freedom.cpp

HEADERS  += keknaizer.h \
    time.h \
    task.h \
    problems.h \
    database.h \
    timeline.h \
    popup.h \
    freedom.h

FORMS    += keknaizer.ui

RESOURCES += \
    db.qrc \
    img.qrc
