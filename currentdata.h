#ifndef CURRENTDATA_H
#define CURRENTDATA_H

class CurrentData
{
public:
    CurrentData();

    int getMinTemp();
    void setMinTemp(int value);
    int getMaxTemp();
    void setMaxTemp(int value);
    int getCurrentTemp();
    void setCurrentTemp(int value);
    int getTargetHumidity();
    void setTargetHumidity(int value);
    int getCurrentHumidity();
    void setCurrentHumidity(int value);
    bool getCurrentWindowState();
    void setCurrentWindowState(bool state);
    bool getCurrentHeaterState();
    void setCurrentHeaterState(bool state);
    bool getOverrideWindow();
    void setOverrideWindow(bool state);
    bool getOverrideHeater();
    void setOverrideHeater(bool state);
    bool getManualWindowState();
    void setManualWindowState(bool state);
    bool getManualHeaterState();
    void setManualHeaterState(bool state);
    bool getAutoTemp();
    void setAutoTemp(bool state);
    bool getAutoHumidity();
    void setAutoHumidity(bool state);

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

