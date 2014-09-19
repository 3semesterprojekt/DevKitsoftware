#include "mainwindow.h"
#include <QApplication>
//#include <QWSServer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QWSServer::setCursorVisible(false);     //hide cursor
    MainWindow w;
    w.show();

    return a.exec();
}
