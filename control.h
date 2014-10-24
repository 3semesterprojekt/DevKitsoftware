#ifndef CONTROL_H
#define CONTROL_H

#include "logfile.h"
#include "currentdata.h"
#include "connection.h"
#include <vector>

class control
{
public:
    control();
    void init(logFile*,CurrentData*);
    void checkValues(int newDevice);
    void dispenseWater(int device, int amount);
private:
    logFile* ptr_logFile;
    CurrentData* ptr_currentData;
    connection* ptr_connection;
    std::vector<int> waterQueue;
    qint64 lastWater;
    int device;
    int numberOfDevices;

};

#endif // CONTROL_H
