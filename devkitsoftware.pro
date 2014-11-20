#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T05:43:29
#
#-------------------------------------------------

QT       += core gui sql
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = devkitsoftware
    target.file = devkitsoftware
    target.path = /home/root
INSTALLS += target
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showdata.cpp \
    changeauto.cpp \
    setmanual.cpp \
    showlog.cpp \
    currentdata.cpp \
    logfile.cpp \
    control.cpp \
    connection.cpp \
    showweather.cpp \
    filedownloader.cpp \
    showbiolex.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    showdata.h \
    changeauto.h \
    setmanual.h \
    showlog.h \
    currentdata.h \
    logfile.h \
    control.h \
    connection.h \
    showweather.h \
    filedownloader.h \
    showbiolex.h \
    database.h

FORMS    += mainwindow.ui \
    showdata.ui \
    changeauto.ui \
    setmanual.ui \
    showlog.ui \
    showweather.ui \
    showbiolex.ui
