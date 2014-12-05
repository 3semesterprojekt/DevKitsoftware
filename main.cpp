#include "mainwindow.h"
#include <QApplication>
#include <QWSServer>
#ifdef __arm__

#endif
//test
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef __arm__

    QWSServer::setCursorVisible(false);     //hide cursor
#endif
    MainWindow w;
    w.show();

    return a.exec();
}
