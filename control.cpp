#include "control.h"
#define TEMPOVERMIN 3
#define TEMPUNDERMAX 2
control::control()
{
    waterqueue = 0;
    lastwater = QDateTime::currentMSecsSinceEpoch() - (2 * 60 * 1000);
}

void control::init(logfile * ptr_log, CurrentData * ptr_data){
    ptr_logfile = ptr_log;
    ptr_currentdata = ptr_data;
    ptr_connection = new connection;
}


void control::checkvalues(){
    //todo: calls are commentet out to debug
    //ptr_currentdata->setcurrenttemp(ptr_connection->gettemp());
    //ptr_currentdata->setcurrentwater(ptr_connection->getwater());

    if(ptr_currentdata->getoverrideheater() == false && ptr_currentdata->getautotemp() == true){ //heater on auto
        if(ptr_currentdata->getcurrenttemp() < ptr_currentdata->getmintemp() && ptr_currentdata->getcurrentheaterstate() == false){ //temperatur is lower that mintemp and heater is off
                ptr_connection->setheater(true);    //turn heater on
                ptr_currentdata->setcurrentheaterstate(true);
                ptr_logfile->setlogevent("Heater has been turned on");
        }

        if(ptr_currentdata->getcurrenttemp() >= ptr_currentdata->getmintemp() + TEMPOVERMIN && ptr_currentdata->getcurrentheaterstate() == true){ //its warm enough, the heater is on
            ptr_connection->setheater(false);    //turn heater of
            ptr_currentdata->setcurrentheaterstate(false);
            ptr_logfile->setlogevent("Heater has been turned off");
        }
    }
    if(ptr_currentdata->getoverrideheater() == true && ptr_currentdata->getcurrentheaterstate() != ptr_currentdata->getmanualheaterstate()){ //heater is on manual override but not set correct
        ptr_connection->setheater(ptr_currentdata->getmanualheaterstate());    //togle heater
        ptr_currentdata->setcurrentheaterstate(ptr_currentdata->getmanualheaterstate());

    }

    if(ptr_currentdata->getoverridewindow() == false && ptr_currentdata->getautotemp() == true){ //window on auto
        if(ptr_currentdata->getcurrenttemp() > ptr_currentdata->getmaxtemp() && ptr_currentdata->getcurrentwindowstate() == false){ //temperatur is higher than maxtemp and window is closed
            ptr_connection->setwindow(true);    //open window
            ptr_currentdata->setcurrentwindowstate(true);
            ptr_logfile->setlogevent("Window has been opened");
        }
        if(ptr_currentdata->getcurrenttemp() <= ptr_currentdata->getmaxtemp() - TEMPUNDERMAX && ptr_currentdata->getcurrentwindowstate() == true){ //temperatur is low enough and window is open
            ptr_connection->setwindow(false);    //close window
            ptr_currentdata->setcurrentwindowstate(false);
            ptr_logfile->setlogevent("Windows has been closed");
        }
    }

    if(ptr_currentdata->getoverridewindow() == true && ptr_currentdata->getcurrentwindowstate() != ptr_currentdata->getmanualwindowstate()){ //window is on manual override but not set correct
        ptr_connection->setwindow(ptr_currentdata->getmanualwindowstate());    //togle window
        ptr_currentdata->setcurrentwindowstate(ptr_currentdata->getmanualwindowstate());
    }

    if(ptr_currentdata->getautowater() == true && ptr_currentdata->getcurrentwater() < ptr_currentdata->gettargetwater()){ //water is on auto and to low
        if(QDateTime::currentMSecsSinceEpoch() - lastwater >= (2 * 60 *1000)){ //only dispence water every 2 minutes
            waterqueue++;
            lastwater = QDateTime::currentMSecsSinceEpoch();
        }
    }
    if( waterqueue > 0){
        ptr_connection->givewater();    //despense water
        waterqueue--;
        QString tmp = "";
        if(waterqueue == 0){
            tmp.append("Dispenced 1dl of water");
        }
        else{
            tmp.append("Dispenced 1dl of water with ");
            tmp.append(QString::number(waterqueue));
            tmp.append("dl stil to go");
        }

        ptr_logfile->setlogevent(tmp);
    }
}

void control::dispensewater(int extrawater){
    waterqueue += extrawater;
}
