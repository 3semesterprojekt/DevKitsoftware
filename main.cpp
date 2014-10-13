#include "mainwindow.h"
#include <QApplication>
#ifdef __arm__
#include <QWSServer>
#endif
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
