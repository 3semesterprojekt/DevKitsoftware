#ifndef CONTROL_H
#define CONTROL_H

#include "logfile.h"
#include "currentdata.h"
#include "connection.h"
#include <vector>
#include <qdebug.h>

class control: public QObject
{
    Q_OBJECT
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
private slots:
    void update(int);
};

#endif // CONTROL_H
