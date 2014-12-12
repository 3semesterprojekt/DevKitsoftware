#include "database.h"

#include <QtSql>
#include <QSqlQuery>
#include<QDebug>



Database::Database()
{
}

void Database::SystemValuesInit(std::vector<CurrentData *> * ptr){

    qDebug() << "sql drivers: " << QSqlDatabase::drivers();
    // get settargethumidity, min and max temp from local db and set
    // get window opened states from local db.
    ptr_currentDataVector = ptr;
    ptr_currentData = ptr_currentDataVector->at(0);

    mydb = QSqlDatabase::addDatabase("QSQLITE");

    Open(mydb);

    QSqlQuery qry;
    QString tableRead = "AutoConfig";
    // read from db

    //QSqlQueryModel *Model = new QSqlQueryModel;
    int readAutoConfig[4];
    qry.exec("SELECT * FROM main.'"+tableRead+"' WHERE AutoConfigId=(SELECT max(AutoConfigId) FROM main.'"+tableRead+"')"); // select max id row
    for(int i = 0; i < 4; i++) // READ AUTOCONFIG
        {
    qry.first();
    readAutoConfig[i] = qry.value(i).toInt();
    qry.next();

        qDebug() << "Autoconfig values (humidity, minTemp, maxTemp): " << readAutoConfig[i];
    }

    //*****************************************************************************
    // READ WINDOWOPEN STATE
    QString table2 = "System";
    QString column2 = "SystemId";
    bool windowOpen;
    bool heaterOn;


    qry.exec("SELECT * FROM main.'"+table2+"' WHERE MeasurementId=(SELECT max(MeasurementId) FROM main.'"+table2+"')"); // select max id row

    qry.first();

    windowOpen = qry.value(5).toBool();
    heaterOn = qry.value(6).toBool();

    qDebug() << "Window open state " << windowOpen;


    ptr_currentData->setCurrentWindowState(windowOpen);// load window og heater states
    ptr_currentData->setCurrentHeaterState(heaterOn);
    qDebug()<< "Current window and heaterstate: " << windowOpen << heaterOn;

    int hum, minTemp, maxTemp; // load humidity og temp

    hum=readAutoConfig[1];
    minTemp = readAutoConfig[2];
    maxTemp = readAutoConfig[3];
    ptr_currentData->setTargetHumidity(hum);
    ptr_currentData->setMinTemp(minTemp);
    ptr_currentData->setMaxTemp(maxTemp);// setting autoconfig


}

void Database::WriteAutoConfigRow(std::vector<CurrentData *> * ptr) // write an autoconfig row DONE
{
    mydb.open();

    QSqlQuery qry;
    QString table = "AutoConfig";
    QString column = "AutoConfigId";
    int id;

    qry.exec("SELECT * FROM main."+table+" WHERE "+column+"=(SELECT max("+column+") FROM main."+table+")"); // select max id row
      qry.first();
      id= qry.value(0).toInt();
      ++id;
      qDebug() <<"Id: "<< id << qry.lastError();

      int hum = ptr_currentData->getTargetHumidity();
      qDebug() << "Current humidity: " << hum;
      int minTemp = ptr_currentData->getMinTemp();
      int maxTemp = ptr_currentData->getMaxTemp();
      QDateTime t = QDateTime::currentDateTime();
      QString time = t.toString();


    qry.exec(QString("insert into main.%1 values (%2,%3,%4,%5,'%6')").arg(table).arg(id).arg(hum).arg(minTemp).arg(maxTemp).arg(time));
    qDebug() << "AutoConfig row written" << qry.lastError();

    //mydb.close();
}



void Database::WriteSystemRow(bool water, int deviceNumber) // writes a row in table Measurement DONE
{
    mydb.open();

    QString table = "Measurement";
    QString column = "MeasurementId";
    // read from db

    int Id;
    QSqlQuery qry;
    qry.exec("SELECT * FROM main."+table+" WHERE "+column+"=(SELECT max("+column+") FROM main."+table+")"); // select max id row


    qry.first();
    Id = qry.value(0).toInt();
    ++Id;

    qDebug() << "MeasurementId : " << Id;

    int humidity = ptr_currentData->getCurrentHumidity();
    int indoorTemp = ptr_currentData->getCurrentTemp();
    int outdoorTemp = ptr_currentData->getCurrentOutTemp();
    QDateTime t = QDateTime::currentDateTime();
    qDebug() << "Time: "<< t;

    QString time = t.toString();
    bool openWindow = ptr_currentData->getCurrentWindowState();
    bool startHeater = ptr_currentData->getCurrentHeaterState();
    bool startWater = water;


    qry.exec(QString("insert into main.'%1' values ('%2','%3','%4','%5','%6','%7','%8','%9','%10')").arg(table).arg(Id).arg(humidity).arg(indoorTemp).arg(outdoorTemp).arg(time).arg(openWindow).arg(startHeater).arg(startWater).arg(deviceNumber));
    qDebug() << qry.lastError();

    qDebug() << "Row written in table measurementRow " << qry.lastError();

    //mydb.close();
}

void Database::WriteMeasurementRow(int sensorId, int measurement) // done
{
    mydb.open();
    QSqlQuery qry;
    QString table = "Sensor";
    QString column = "SensorId";
    int Id;
    // read from db
    qry.exec("SELECT * FROM main."+table+" WHERE "+column+"=(SELECT max("+column+") FROM main."+table+")"); // select max id row

    qry.first();
    Id = qry.value(0).toInt();
    ++Id;

    qDebug() << "Sensor id : " << Id;

    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString();

    qDebug() << "Time: "<< t;

    qry.exec(QString("insert into main.%1 values ('%2','%3','%4','%5')").arg(table).arg(Id).arg(sensorId).arg(measurement).arg(time));
    //qDebug() << qry.lastError();
    //mydb.close();

}

void Database::WriteSensorRow(QString sensorName, int measurement, int id) // done
{
    mydb.open();
    QSqlQuery qry;
    QString table = "Sensor";

    int Id;

    qDebug() << "Sensor id : " << Id;

    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString();

    qDebug() << "Time: "<< t;

    qry.exec(QString("insert into main.%1 values ('%2','%3','%4','%5')").arg(table).arg(id).arg(sensorName).arg(measurement).arg(time));
    //qDebug() << qry.lastError();
    //mydb.close();

}



void Database::Close()
{
    mydb.close();
}

void Database::Open(QSqlDatabase mydb){
#ifdef __arm__
    mydb.setDatabaseName("/home/root/ghdb.sqlite"); // database path on devkit
#else
    mydb.setDatabaseName("/home/stud/sqlite/ghdb.sqlite"); // database path on PC
#endif
    mydb.open();
    if(mydb.open())
        {
    qDebug() << "Database connection established";
        }
    else
        {
    qDebug() << "Database connection error";
        }
}

