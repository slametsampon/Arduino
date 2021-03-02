/*
  fireSensor.h - Library untuk FireSensor
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "fireSensor.h"

FireSensor::FireSensor(char pin):_pin(pin){}

void FireSensor::setParameter(parameter *param){
    _parameter = param;
}

parameter *FireSensor::getParameter(){
    return _parameter;
}

String FireSensor::toString(){
  String str = _parameter->id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _parameter->unit);
  if (_parameter->lowAlarm){
    alm = "(L)";
  }
  if (_parameter->highAlarm){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

char FireSensor::getStatus(){
    char sts = NORMAL;
    if (_parameter->lowAlarm){
        sts = LOW_ALARM;
    }
    if (_parameter->highAlarm){
        sts = HIGH_ALARM;
    }
    return sts;
}

