#include "currentdata.h"

CurrentData::CurrentData(){

    minTemp = 20;
    maxTemp = 26;
    currentTemp = 23;
    targetHumidity = 45;
    currentHumidity = 47;
    currentWindowState = 0;
    currentHeaterState = 0;
    overrideWindow = 0;
    overrideHeater = 0;
    manualWindowState = 0;
    manualHeaterState = 0;
    autoTemp = 1;
    autoHumidity = 1;
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
    currentTemp = tmp;
    emit currentDataChanged();
}

int CurrentData::getTargetHumidity(){
    return targetHumidity;
}

void CurrentData::setTargetHumidity(int tmp){
    targetHumidity = tmp;
}

int CurrentData::getCurrentHumidity(){
    return currentHumidity;
}

void CurrentData::setCurrentHumidity(int tmp){
    currentHumidity = tmp;
    emit currentDataChanged();
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
}

bool CurrentData::getOverrideHeater(){
    return overrideHeater;
}

void CurrentData::setOverrideHeater(bool tmp){
    overrideHeater = tmp;
}

bool CurrentData::getManualWindowState(){
    return manualWindowState;
}

void CurrentData::setManualWindowState(bool tmp){
    manualWindowState = tmp;
}

bool CurrentData::getManualHeaterState(){
    return manualHeaterState;
}

void CurrentData::setManualHeaterState(bool tmp){
    manualHeaterState = tmp;
}

bool CurrentData::getAutoTemp(){
    return autoTemp;
}

void CurrentData::setAutoTemp(bool tmp){
    autoTemp = tmp;
}

bool CurrentData::getAutoHumidity(){
    return autoHumidity;
}

void CurrentData::setAutoHumidity(bool tmp){
    autoHumidity = tmp;
}

