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
    void checkvalues();
    void dispensewater(int);
private:
    logfile* ptr_logfile;
    CurrentData* ptr_currentdata;
    connection* ptr_connection;
    int waterqueue;

};

#endif // CONTROL_H
