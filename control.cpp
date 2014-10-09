#include "control.h"
#define TEMPOVERMIN 3
#define TEMPUNDERMAX 2
control::control()
{
    waterQueue = 0;
    lastWater = QDateTime::currentMSecsSinceEpoch() - (2 * 60 * 1000);
}

void control::init(logfile * ptr_log, CurrentData * ptr_data){
    ptr_logfile = ptr_log;
    ptr_currentdata = ptr_data;
    ptr_connection = new connection;
}


void control::checkValues(){
    //todo: calls are commentet out to debug
    //ptr_currentdata->setcurrenttemp(ptr_connection->gettemp());
    //ptr_currentdata->setcurrentwater(ptr_connection->getwater());

    if(ptr_currentdata->getOverrideHeater() == false && ptr_currentdata->getAutoTemp() == true){ //heater on auto
        if(ptr_currentdata->getCurrentTemp() < ptr_currentdata->getMinTemp() && ptr_currentdata->getCurrentHeaterState() == false){ //temperatur is lower that mintemp and heater is off
                ptr_connection->setHeater(true);    //turn heater on
                ptr_currentdata->setCurrentHeaterState(true);
                ptr_logfile->setLogEvent("Heater has been turned on");
        }

        if(ptr_currentdata->getCurrentTemp() >= ptr_currentdata->getMinTemp() + TEMPOVERMIN && ptr_currentdata->getCurrentHeaterState() == true){ //its warm enough, the heater is on
            ptr_connection->setHeater(false);    //turn heater of
            ptr_currentdata->setCurrentHeaterState(false);
            ptr_logfile->setLogEvent("Heater has been turned off");
        }
    }
    if(ptr_currentdata->getOverrideHeater() == true && ptr_currentdata->getCurrentHeaterState() != ptr_currentdata->getManualHeaterState()){ //heater is on manual override but not set correct
        ptr_connection->setHeater(ptr_currentdata->getManualHeaterState());    //togle heater
        ptr_currentdata->setCurrentHeaterState(ptr_currentdata->getManualHeaterState());

    }

    if(ptr_currentdata->getOverrideWindow() == false && ptr_currentdata->getAutoTemp() == true){ //window on auto
        if(ptr_currentdata->getCurrentTemp() > ptr_currentdata->getMaxTemp() && ptr_currentdata->getCurrentWindowState() == false){ //temperatur is higher than maxtemp and window is closed
            ptr_connection->setWindow(true);    //open window
            ptr_currentdata->setCurrentWindowState(true);
            ptr_logfile->setLogEvent("Window has been opened");
        }
        if(ptr_currentdata->getCurrentTemp() <= ptr_currentdata->getMaxTemp() - TEMPUNDERMAX && ptr_currentdata->getCurrentWindowState() == true){ //temperatur is low enough and window is open
            ptr_connection->setWindow(false);    //close window
            ptr_currentdata->setCurrentWindowState(false);
            ptr_logfile->setLogEvent("Windows has been closed");
        }
    }

    if(ptr_currentdata->getOverrideWindow() == true && ptr_currentdata->getCurrentWindowState() != ptr_currentdata->getManualWindowState()){ //window is on manual override but not set correct
        ptr_connection->setWindow(ptr_currentdata->getManualWindowState());    //togle window
        ptr_currentdata->setCurrentWindowState(ptr_currentdata->getManualWindowState());
    }

    if(ptr_currentdata->getAutoHumidity() == true && ptr_currentdata->getCurrentHumidity() < ptr_currentdata->getTargetHumidity()){ //water is on auto and to low
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

        ptr_logfile->setLogEvent(tmp);
    }
}

void control::dispenseWater(int extraWater){
    waterQueue += extraWater;
}
