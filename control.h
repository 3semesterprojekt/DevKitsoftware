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
    void checkValues(int newDevice);
    void dispenseWater(int device, int amount);
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
    void update(int);
};

#endif // CONTROL_H
