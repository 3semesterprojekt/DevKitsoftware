#include "control.h"
#define TEMPOVERMIN 3
#define TEMPUNDERMAX 2
control::control()
{
    waterQueue = 0;
    lastWater = QDateTime::currentMSecsSinceEpoch() - (2 * 60 * 1000);
}

void control::init(logFile * ptr_log, CurrentData * ptr_data){
    ptr_logFile = ptr_log;
    ptr_currentData = ptr_data;
    ptr_connection = new connection;
}


void control::checkValues(){
    //todo: calls are commentet out to debug
    //ptr_currentdata->setcurrenttemp(ptr_connection->gettemp());
    //ptr_currentdata->setcurrentwater(ptr_connection->getwater());

    if(ptr_currentData->getOverrideHeater() == false && ptr_currentData->getAutoTemp() == true){ //heater on auto
        if(ptr_currentData->getCurrentTemp() < ptr_currentData->getMinTemp() && ptr_currentData->getCurrentHeaterState() == false){ //temperatur is lower that mintemp and heater is off
                ptr_connection->setHeater(true);    //turn heater on
                ptr_currentData->setCurrentHeaterState(true);
                ptr_logFile->setLogEvent("Heater has been turned on");
        }

        if(ptr_currentData->getCurrentTemp() >= ptr_currentData->getMinTemp() + TEMPOVERMIN && ptr_currentData->getCurrentHeaterState() == true){ //its warm enough, the heater is on
            ptr_connection->setHeater(false);    //turn heater of
            ptr_currentData->setCurrentHeaterState(false);
            ptr_logFile->setLogEvent("Heater has been turned off");
        }
    }
    if(ptr_currentData->getOverrideHeater() == true && ptr_currentData->getCurrentHeaterState() != ptr_currentData->getManualHeaterState()){ //heater is on manual override but not set correct
        ptr_connection->setHeater(ptr_currentData->getManualHeaterState());    //togle heater
        ptr_currentData->setCurrentHeaterState(ptr_currentData->getManualHeaterState());

    }

    if(ptr_currentData->getOverrideWindow() == false && ptr_currentData->getAutoTemp() == true){ //window on auto
        if(ptr_currentData->getCurrentTemp() > ptr_currentData->getMaxTemp() && ptr_currentData->getCurrentWindowState() == false){ //temperatur is higher than maxtemp and window is closed
            ptr_connection->setWindow(true);    //open window
            ptr_currentData->setCurrentWindowState(true);
            ptr_logFile->setLogEvent("Window has been opened");
        }
        if(ptr_currentData->getCurrentTemp() <= ptr_currentData->getMaxTemp() - TEMPUNDERMAX && ptr_currentData->getCurrentWindowState() == true){ //temperatur is low enough and window is open
            ptr_connection->setWindow(false);    //close window
            ptr_currentData->setCurrentWindowState(false);
            ptr_logFile->setLogEvent("Windows has been closed");
        }
    }

    if(ptr_currentData->getOverrideWindow() == true && ptr_currentData->getCurrentWindowState() != ptr_currentData->getManualWindowState()){ //window is on manual override but not set correct
        ptr_connection->setWindow(ptr_currentData->getManualWindowState());    //togle window
        ptr_currentData->setCurrentWindowState(ptr_currentData->getManualWindowState());
    }

    if(ptr_currentData->getAutoHumidity() == true && ptr_currentData->getCurrentHumidity() < ptr_currentData->getTargetHumidity()){ //water is on auto and to low
        if(QDateTime::currentMSecsSinceEpoch() - lastWater >= (2 * 60 *1000)){ //only dispence water every 2 minutes
            waterQueue++;
            lastWater = QDateTime::currentMSecsSinceEpoch();
        }
    }
    if( waterQueue > 0){
        ptr_connection->giveWater();    //despense water
        waterQueue--;
        QString tmp = "";
        if(waterQueue == 0){
            tmp.append("Dispenced 1dl of water");
        }
        else{
            tmp.append("Dispenced 1dl of water with ");
            tmp.append(QString::number(waterQueue));
            tmp.append("dl stil to go");
        }

        ptr_logFile->setLogEvent(tmp);
    }
}

void control::dispenseWater(int extraWater){
    waterQueue += extraWater;
}
