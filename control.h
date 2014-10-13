#ifndef CONTROL_H
#define CONTROL_H

#include "logfile.h"
#include "currentdata.h"
#include "connection.h"

class control
{
public:
    control();
    void init(logFile*,CurrentData*);
    void checkValues();
    void dispenseWater(int amount);
private:
    logFile* ptr_logFile;
    CurrentData* ptr_currentData;
    connection* ptr_connection;
    int waterQueue;
    qint64 lastWater;
    int device;

};

#endif // CONTROL_H
