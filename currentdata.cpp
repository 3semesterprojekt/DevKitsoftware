#include "currentdata.h"

CurrentData::CurrentData(){

    mintemp = 0;
    maxtemp = 0;
    currenttemp = 23;
    targetwater = 0;
    currentwater = 430;
    currentwindowstate = 0;
    currentheaterstate = 0;
    overridewindow = 0;
    overrideheater = 0;
    manualwindowstate = 0;
    manualheaterstate = 0;
    autotemp = 0;
    autowater = 0;
}

int CurrentData::getmintemp(){
    return mintemp;
}

void CurrentData::setmintemp(int tmp){
    mintemp = tmp;
}

int CurrentData::getmaxtemp(){
    return maxtemp;
}

void CurrentData::setmaxtemp(int tmp){
    maxtemp = tmp;
}

int CurrentData::getcurrenttemp(){
    return currenttemp;
}

void CurrentData::setcurrenttemp(int tmp){
    currenttemp = tmp;
}

int CurrentData::gettargetwater(){
    return targetwater;
}

void CurrentData::settargetwater(int tmp){
    targetwater = tmp;
}

int CurrentData::getcurrentwater(){
    return currentwater;
}

void CurrentData::setcurrentwater(int tmp){
    currentwater = tmp;
}

bool CurrentData::getcurrentwindowstate(){
    return currentwindowstate;
}

void CurrentData::setcurrentwindowstate(bool tmp){
    currentwindowstate = tmp;
}

bool CurrentData::getcurrentheaterstate(){
    return currentheaterstate;
}

void CurrentData::setcurrentheaterstate(bool tmp){
    currentheaterstate = tmp;
}

bool CurrentData::getoverridewindow(){
    return overridewindow;
}

void CurrentData::setoverridewindow(bool tmp){
    overridewindow = tmp;
}

bool CurrentData::getoverrideheater(){
    return overrideheater;
}

void CurrentData::setoverrideheater(bool tmp){
    overrideheater = tmp;
}

bool CurrentData::getmanualwindowstate(){
    return manualwindowstate;
}

void CurrentData::setmanualwindowstate(bool tmp){
    manualwindowstate = tmp;
}

bool CurrentData::getmanualheaterstate(){
    return manualheaterstate;
}

void CurrentData::setmanualheaterstate(bool tmp){
    manualheaterstate = tmp;
}

bool CurrentData::getautotemp(){
    return autotemp;
}

void CurrentData::setautotemp(bool tmp){
    autotemp = tmp;
}

bool CurrentData::getautowater(){
    return autowater;
}

void CurrentData::setautowater(bool tmp){
    autowater = tmp;
}

