#include "database.h"

#include <QtSql>
#include <QSqlQuery>
#include<QDebug>



Database::Database()
{


}

void Database::SystemValuesInit(std::vector<CurrentData *> * ptr){

    // get settargethumidity, min and max temp from local db and set
// get window opened states from local db.
    ptr_currentDataVector = ptr;
    ptr_currentData = ptr_currentDataVector->at(0);

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/root/ghdb.sqlite"); // database path on devkit
    mydb.open();
    if(mydb.open())
        {
    qDebug() << "Database connection established";
        }
    else
        {
    qDebug() << "Database connection error";
        }

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
    QString table2 = "Measurement";
    QString column2 = "MeasurementId";
    bool windowOpen;


    qry.exec("SELECT * FROM main.'"+table2+"' WHERE MeasurementId=(SELECT max(MeasurementId) FROM main.'"+table2+"')"); // select max id row

    qry.first();
    windowOpen = qry.value(5).toBool();


    qDebug() << "Window open state " << windowOpen;

    bool heaterState = windowOpen;


    ptr_currentData->setCurrentHeaterState(heaterState);// load window og heater states

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


    qry.exec(QString("insert into main.%1 values (%2,%3,%4,%5)").arg(table).arg(id).arg(hum).arg(minTemp).arg(maxTemp));
    qDebug() << "AutoConfig row written" << qry.lastError();

    mydb.close();
}



void Database::WriteMeasurementRow(bool water, int deviceNumber) // writes a row in table Measurement DONE
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

    QString time = t.toString();// TODO: get time
    bool openWindow = ptr_currentData->getCurrentWindowState();
    bool autoMode = true;// todo get system mode
    bool startHeater = ptr_currentData->getCurrentHeaterState();
    bool startWater = water;


    qry.exec(QString("insert into main.'%1' values ('%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')").arg(table).arg(Id).arg(humidity).arg(indoorTemp).arg(outdoorTemp).arg(time).arg(openWindow).arg(autoMode).arg(startHeater).arg(startWater).arg(deviceNumber));
    qDebug() << qry.lastError();



    qDebug() << "Row written in table measurementRow " << qry.lastError();

    mydb.close();
}

void Database::WriteSensorRow(QString sensorName, int measurement) // done
{
    mydb.open();
    QSqlQuery qry;
    QString table = "Sensor";
    QString column = "SensorId";
    // read from db

    int Id;
    qry.exec("SELECT * FROM main."+table+" WHERE "+column+"=(SELECT max("+column+") FROM main."+table+")"); // select max id row


    qry.first();
    Id = qry.value(0).toInt();
    ++Id;

    qDebug() << "Sensor id : " << Id;

    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString();
    QString ti= time;
    qDebug() << "Time: "<< t;

    qry.exec(QString("insert into main.%1 values ('%2','%3','%4','%5')").arg(table).arg(Id).arg(sensorName).arg(measurement).arg(time));
    qDebug() << qry.lastError();
    mydb.close();

}



void Database::SendToBackend()
{
    // send whole local db to backend
    // do this every...
}

void Database::Close()
{
    mydb.close();
}

