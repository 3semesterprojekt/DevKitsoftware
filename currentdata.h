#ifndef CURRENTDATA_H
#define CURRENTDATA_H

class CurrentData
{
public:
    CurrentData();

    int getmintemp();
    void setmintemp(int);
    int getmaxtemp();
    void setmaxtemp(int);
    int getcurrenttemp();
    void setcurrenttemp(int);
    int gettargetwater();
    void settargetwater(int);
    int getcurrentwater();
    void setcurrentwater(int);
    bool getcurrentwindowstate();
    void setcurrentwindowstate(bool);
    bool getcurrentheaterstate();
    void setcurrentheaterstate(bool);
    bool getoverridewindow();
    void setoverridewindow(bool);
    bool getoverrideheater();
    void setoverrideheater(bool);
    bool getmanualwindowstate();
    void setmanualwindowstate(bool);
    bool getmanualheaterstate();
    void setmanualheaterstate(bool);
    bool getautotemp();
    void setautotemp(bool);
    bool getautowater();
    void setautowater(bool);

private:
    int mintemp;    //minimum automatic temperatur
    int maxtemp;    //maximum automatic temperatur
    int currenttemp;    //current temperatur
    int targetwater;    //target automatic water value
    int currentwater;   // current water value
    bool currentwindowstate;    //state of the window (open/close)
    bool currentheaterstate;    //state of the heater (on/off)
    bool overridewindow;    //manual window override
    bool overrideheater;    //manual heater overrride
    bool manualwindowstate;
    bool manualheaterstate;
    bool autotemp;  //is the temperatur in automatic mode
    bool autowater; //is the water in automatic mode
};

#endif  //CURRENTDATA_H
