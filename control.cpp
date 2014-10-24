#include "control.h"
#define TEMPOVERMIN 3
#define TEMPUNDERMAX 2
control::control()
{
    numberOfDevices = 1; //TODO
    for(int i = 0; i < numberOfDevices; i++){
        waterQueue.push_back(0);
    }
    lastWater = QDateTime::currentMSecsSinceEpoch() - (2 * 60 * 1000);
}

void control::init(logFile * ptr_log, CurrentData * ptr_data){
    ptr_logFile = ptr_log;
    ptr_currentData = ptr_data;
    ptr_connection = new connection;
}


void control::checkValues(int newDevice){
    device = newDevice;
    ptr_connection->getValues(device);
    //TODO: calls are commentet out to debug
    //ptr_currentData->setCurrentTemp(ptr_connection->getTemp());
    //ptr_currentData->setCurrentHumidity(ptr_connection->getHumidity());

    if(ptr_currentData->getOverrideHeater() == false && ptr_currentData->getAutoTemp() == true){ //heater on auto
        if(ptr_currentData->getCurrentTemp() < ptr_currentData->getMinTemp() && ptr_currentData->getCurrentHeaterState() == false){ //temperatur is lower that mintemp and heater is off
                ptr_connection->setHeater(device, true);    //turn heater on
                ptr_currentData->setCurrentHeaterState(true);
                ptr_logFile->setLogEvent("Heater has been turned on");
        }

        if(ptr_currentData->getCurrentTemp() >= ptr_currentData->getMinTemp() + TEMPOVERMIN && ptr_currentData->getCurrentHeaterState() == true){ //its warm enough, the heater is on
            ptr_connection->setHeater(device, false);    //turn heater of
            ptr_currentData->setCurrentHeaterState(false);
            ptr_logFile->setLogEvent("Heater has been turned off");
        }
    }
    if(ptr_currentData->getOverrideHeater() == true && ptr_currentData->getCurrentHeaterState() != ptr_currentData->getManualHeaterState()){ //heater is on manual override but not set correct
        ptr_connection->setHeater(device, ptr_currentData->getManualHeaterState());    //togle heater
        ptr_currentData->setCurrentHeaterState(ptr_currentData->getManualHeaterState());
        if(ptr_currentData->getManualHeaterState() == true){
            ptr_logFile->setLogEvent("Heater has been turned on");
        }
        else{
            ptr_logFile->setLogEvent("Heater has been turned off");
        }
    }

    if(ptr_currentData->getOverrideWindow() == false && ptr_currentData->getAutoTemp() == true){ //window on auto
        if(ptr_currentData->getCurrentTemp() > ptr_currentData->getMaxTemp() && ptr_currentData->getCurrentWindowState() == false){ //temperatur is higher than maxtemp and window is closed
            ptr_connection->setWindow(device, true);    //open window
            ptr_currentData->setCurrentWindowState(true);
            ptr_logFile->setLogEvent("Window has been opened");
        }
        if(ptr_currentData->getCurrentTemp() <= ptr_currentData->getMaxTemp() - TEMPUNDERMAX && ptr_currentData->getCurrentWindowState() == true){ //temperatur is low enough and window is open
            ptr_connection->setWindow(device, false);    //close window
            ptr_currentData->setCurrentWindowState(false);
            ptr_logFile->setLogEvent("Window has been closed");
        }
    }

    if(ptr_currentData->getOverrideWindow() == true && ptr_currentData->getCurrentWindowState() != ptr_currentData->getManualWindowState()){ //window is on manual override but not set correct
        ptr_connection->setWindow(device, ptr_currentData->getManualWindowState());    //togle window
        ptr_currentData->setCurrentWindowState(ptr_currentData->getManualWindowState());
        if(ptr_currentData->getManualWindowState() == true){
            ptr_logFile->setLogEvent("Window has been opened");
        }
        else{
            ptr_logFile->setLogEvent("Window has been closed");
        }
    }

    if(ptr_currentData->getAutoHumidity() == true && ptr_currentData->getCurrentHumidity() < ptr_currentData->getTargetHumidity()){ //water is on auto and to low
        if(QDateTime::currentMSecsSinceEpoch() - lastWater >= (2 * 60 *1000)){ //only dispence water every 2 minutes
            waterQueue.at(device)++;
            lastWater = QDateTime::currentMSecsSinceEpoch();
        }
    }
    if( waterQueue.at(device) > 0){
        ptr_connection->giveWater(device);    //despense water
        waterQueue.at(device)--;
        QString tmp = "";
        if(waterQueue.at(device) == 0){
            tmp.append("Dispenced 1dl of water");
        }
        else{
            tmp.append("Dispenced 1dl of water with ");
            tmp.append(QString::number(waterQueue.at(device)));
            tmp.append("dl stil to go");
        }

        ptr_logFile->setLogEvent(tmp);
    }
}

void control::dispenseWater(int device, int extraWater){
    waterQueue.at(device) += extraWater;
}
