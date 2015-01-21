#ifndef CONTROL_H
#define CONTROL_H

#include "logfile.h"
#include "currentdata.h"
#include "connection.h"
#include <vector>
#include <qdebug.h>
#include "database.h"

class control: public QObject
{
    Q_OBJECT
public:
    control();
    void init(logFile*,CurrentData*, Database*);
    void dispenseWater(int device, int amount);

    void updateSystemValues(int device);
    void manualHumidityControl(int device);
    void autoHumidityControl(int device);
    void autoTempControl(int device);

private:
    logFile* ptr_logFile;
    CurrentData* ptr_currentData;
    connection* ptr_connection;
    std::vector<int> waterQueue;
    qint64 lastWater;
    Database* ptr_database;
    int device;
    int numberOfDevices;
private slots:
    void manualTempControl(int device, int type);
};

#endif // CONTROL_H
