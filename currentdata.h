#ifndef CURRENTDATA_H
#define CURRENTDATA_H

class CurrentData
{
public:
    CurrentData();

    int getMinTemp();
    void setMinTemp(int);
    int getMaxTemp();
    void setMaxTemp(int);
    int getCurrentTemp();
    void setCurrentTemp(int);
    int getTargetHumidity();
    void setTargetHumidity(int);
    int getCurrentHumidity();
    void setCurrentHumidity(int);
    bool getCurrentWindowState();
    void setCurrentWindowState(bool);
    bool getCurrentHeaterState();
    void setCurrentHeaterState(bool);
    bool getOverrideWindow();
    void setOverrideWindow(bool);
    bool getOverrideHeater();
    void setOverrideHeater(bool);
    bool getManualWindowState();
    void setManualWindowState(bool);
    bool getManualHeaterState();
    void setManualHeaterState(bool);
    bool getAutoTemp();
    void setAutoTemp(bool);
    bool getAutoHumidity();
    void setAutoHumidity(bool);

private:
    int minTemp;    //minimum automatic temperatur
    int maxTemp;    //maximum automatic temperatur
    int currentTemp;    //current temperatur
    int targetHumidity;    //target automatic water value
    int currentHumidity;   // current water value
    bool currentWindowState;    //state of the window (open/close)
    bool currentHeaterState;    //state of the heater (on/off)
    bool overrideWindow;    //manual window override
    bool overrideHeater;    //manual heater overrride
    bool manualWindowState;
    bool manualHeaterState;
    bool autoTemp;  //is the temperatur in automatic mode
    bool autoHumidity; //is the water in automatic mode
};

#endif  //CURRENTDATA_H

