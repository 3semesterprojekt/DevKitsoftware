#include "control.h"
#define TEMPOVERMIN 3
#define TEMPUNDERMAX 2
control::control() // TODO create db inserts for every event
{
    numberOfDevices = 1; //TODO
    for(int i = 0; i < numberOfDevices; i++){
        waterQueue.push_back(0);
    }
    lastWater = QDateTime::currentMSecsSinceEpoch() - (2 * 60 * 1000);
}

void control::init(logFile * ptr_log, CurrentData * ptr_data, Database* ptr_db){
    ptr_logFile = ptr_log;
    ptr_currentData = ptr_data;
    ptr_connection = new connection;
    ptr_database = ptr_db;
    connect(ptr_currentData, SIGNAL(manualOverrideChanged(int)), this, SLOT(manualTempControl(int)));
    ptr_connection->init(ptr_database);
}

void control::dispenseWater(int device, int extraWater){
    waterQueue.at(device) += extraWater;
    ptr_connection->getValues(device);
}

void control::updateSystemValues(int device){
    ptr_connection->getValues(device);
    ptr_currentData->setCurrentTemp(ptr_connection->getTemp());
    ptr_currentData->setCurrentHumidity(ptr_connection->getHumidity());
    ptr_currentData->setCurrentOutTemp(ptr_connection->getOutTemp());
    if(waterQueue.at(device) > 0){
        ptr_connection->giveWater(device);
        waterQueue.at(device)--;
        ptr_database->WriteSystemRow(1,device);
        QString tmp = "";
        if(waterQueue.at(device) == 0){
            tmp.append("Dispenced 500ml of water");
        }
        else{
            tmp.append("Dispenced 500ml of water with ");
            tmp.append(QString::number(waterQueue.at(device)*500));
            tmp.append("ml stil to go");
        }
        ptr_logFile->setLogEvent(tmp);
    }
}

void control::manualTempControl(int device){
    if(ptr_currentData->getOverrideHeater()){ //heater is on manual
        ptr_connection->setHeater(device, ptr_currentData->getManualHeaterState()); //set heater to userinput
        ptr_database->WriteSystemRow(0,device);
        if(ptr_currentData->getManualHeaterState()){
            ptr_logFile->setLogEvent("Heater has been activated");
        }
        else{
            ptr_logFile->setLogEvent("Heater has been deactivated");
        }
    }
    if(ptr_currentData->getOverrideWindow()){ //window is on manual
        ptr_connection->setWindow(device, ptr_currentData->getManualWindowState());
        ptr_database->WriteSystemRow(0,device);
        if(ptr_currentData->getManualWindowState()){
            ptr_logFile->setLogEvent("Window has been opened");
        }
        else{
            ptr_logFile->setLogEvent("Window has been closed");
        }
    }
    ptr_connection->getValues(device);
}

void control::autoHumidityControl(int device){
    if(ptr_currentData->getAutoHumidity()){//automatic humidity control is on
        if(QDateTime::currentMSecsSinceEpoch() - lastWater >= (2 * 60 *1000)){ //only dispence water every 2 minutes
            if(ptr_currentData->getCurrentHumidity() < ptr_currentData->getTargetHumidity()){ //only add water if the system is to dry
                waterQueue.at(device)++;
                lastWater = QDateTime::currentMSecsSinceEpoch();
                ptr_database->WriteSystemRow(1,device);
            }
        }
    }
}

void control::autoTempControl(int device){
    if(ptr_currentData->getAutoTemp()){ //automatic temp control is on
        if(!ptr_currentData->getOverrideHeater()){ //heater is not on override
            if(ptr_currentData->getCurrentTemp() < (ptr_currentData->getMinTemp())){ //temperature is under minimum
                ptr_connection->setHeater(device, true);
                ptr_logFile->setLogEvent("Heater has been activated");
                ptr_database->WriteSystemRow(0,device);
            }
            if(ptr_currentData->getCurrentTemp() > (ptr_currentData->getMinTemp() +3)){ //temperatur is 3° over minimum
                ptr_connection->setHeater(device, false);
                ptr_logFile->setLogEvent("Heater has been deactivated");
            }
        }
        if(!ptr_currentData->getOverrideWindow()){ //window is not on override
            if(ptr_currentData->getCurrentTemp() > ptr_currentData->getMaxTemp()){ //temperature is over maximum
                ptr_connection->setWindow(device, true);
                ptr_logFile->setLogEvent("window has been opened");
                ptr_database->WriteSystemRow(0,device);
            }
            if(ptr_currentData->getCurrentTemp() < (ptr_currentData->getMaxTemp() +3)){ //temperature is 3° under maximum
                ptr_connection->setWindow(device, false);
                ptr_logFile->setLogEvent("window has been closed");
                ptr_database->WriteSystemRow(0,device);
            }
        }
    }
}
