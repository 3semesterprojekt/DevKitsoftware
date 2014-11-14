#include "currentdata.h"

CurrentData::CurrentData(){

    minTemp = 20;
    maxTemp = 30;
    currentTemp = 0;
    currentOutTemp = 0;
    targetHumidity = 45;
    currentHumidity = 0;
    currentWindowState = 0;
    currentHeaterState = 0;
    overrideWindow = 0;
    overrideHeater = 0;
    manualWindowState = 0;
    manualHeaterState = 0;
    autoTemp = 0;
    autoHumidity = 0;
}

int CurrentData::getMinTemp(){
    return minTemp;
}

void CurrentData::setMinTemp(int tmp){
    minTemp = tmp;
}

int CurrentData::getMaxTemp(){
    return maxTemp;
}

void CurrentData::setMaxTemp(int tmp){
    maxTemp = tmp;
}

int CurrentData::getCurrentTemp(){
    return currentTemp;
}

void CurrentData::setCurrentTemp(int tmp){
    if(tmp < 50 && tmp > -10){
        currentTemp = tmp;
        emit currentDataChanged();
    }
}

int CurrentData::getCurrentOutTemp(){
    return currentOutTemp;
}

void CurrentData::setCurrentOutTemp(int tmp){
    if(tmp < 50 && tmp > -10){
        currentOutTemp = tmp;
        emit currentDataChanged();
    }
}

int CurrentData::getTargetHumidity(){
    return targetHumidity;
}

void CurrentData::setTargetHumidity(int tmp){
    if(tmp < 100 && tmp > 0){
        targetHumidity = tmp;
    }
}

int CurrentData::getCurrentHumidity(){
    return currentHumidity;
}

void CurrentData::setCurrentHumidity(int tmp){
    if(tmp < 100 && tmp > 0){
        currentHumidity = tmp;
        emit currentDataChanged();
    }
}

bool CurrentData::getCurrentWindowState(){
    return currentWindowState;
}

void CurrentData::setCurrentWindowState(bool tmp){
    currentWindowState = tmp;
}

bool CurrentData::getCurrentHeaterState(){
    return currentHeaterState;
}

void CurrentData::setCurrentHeaterState(bool tmp){
    currentHeaterState = tmp;
}

bool CurrentData::getOverrideWindow(){
    return overrideWindow;
}

void CurrentData::setOverrideWindow(bool tmp){
    overrideWindow = tmp;
    emit statusChanged();
}

bool CurrentData::getOverrideHeater(){
    return overrideHeater;
}

void CurrentData::setOverrideHeater(bool tmp){
    overrideHeater = tmp;
    emit statusChanged();
}

bool CurrentData::getManualWindowState(){
    return manualWindowState;
}

void CurrentData::setManualWindowState(bool tmp){
    manualWindowState = tmp;
    emit manualOverrideChanged(deviceID);
}

bool CurrentData::getManualHeaterState(){
    return manualHeaterState;
}

void CurrentData::setManualHeaterState(bool tmp){
    manualHeaterState = tmp;
    emit manualOverrideChanged(deviceID);
}

bool CurrentData::getAutoTemp(){
    return autoTemp;
}

void CurrentData::setAutoTemp(bool tmp){
    autoTemp = tmp;
    emit statusChanged();
}

bool CurrentData::getAutoHumidity(){
    return autoHumidity;
}

void CurrentData::setAutoHumidity(bool tmp){
    autoHumidity = tmp;
    emit statusChanged();
}

void CurrentData::setDeviceName(QString name){
    deviceName = name;
    return;
}

QString CurrentData::getDeviceName(){
    return deviceName;
}

void CurrentData::setDeviceID(int id){
    deviceID = id;
}

int CurrentData::getDeviceID(){
    return deviceID;
}
