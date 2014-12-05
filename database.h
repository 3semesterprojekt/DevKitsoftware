#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include<QDebug>
#include "showbiolex.h"
#include <QDateTime>

class Database : QObject
{
public:
    Database();
    void SystemValuesInit(std::vector<CurrentData *> * ptr);
    void AddToDb(QString data ,QString tableName, QString column);


    void SendToBackend();
    QString dbName;

    void Close();
    void Open(QSqlDatabase);

    QSqlDatabase mydb;

    void WriteMeasurementRow(bool water, int deviceNumber);
    void WriteAutoConfigRow(std::vector<CurrentData *> * ptr);
    void WriteSensorRow(QString sensorName, int measurement);

    Database *ptr_database;

private:



    CurrentData* ptr_currentData;
    std::vector<CurrentData*> *ptr_currentDataVector;


};

#endif // DATABASE_H
