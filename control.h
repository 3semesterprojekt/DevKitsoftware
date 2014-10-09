#ifndef CONTROL_H
#define CONTROL_H

#include "logfile.h"
#include "currentdata.h"
#include "connection.h"

class control
{
public:
    control();
    void init(logfile*,CurrentData*);
    void checkValues();
    void dispenseWater(int);
private:
    logfile* ptr_logfile;
    CurrentData* ptr_currentdata;
    connection* ptr_connection;
    int waterQueue;
    qint64 lastWater;

};

#endif // CONTROL_H
