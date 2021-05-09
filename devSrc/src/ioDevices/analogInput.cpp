/*
  analogInput.h - Library AI
  with AlfaEma filter
  By : Sam April 03, 2021
*/

/* Dependencies */
#include "analogInput.h"

AnalogInput::AnalogInput(int pin):
_pin(pin), _id("AnalogInput"), _pullUp(PULLUP_NONE){
  _device = _id;
  pinMode(_pin, INPUT);
}

void AnalogInput::init(boolean typ){
  _pullUp = typ;

  if (typ == PULLUP)pinMode(_pin, INPUT_PULLUP);
  else pinMode(_pin, INPUT);
}

void AnalogInput::init(boolean typ, String id){
  _id = id;
  this->init(typ);
}

void AnalogInput::setParam(param dataParam){

  _dataParam = dataParam;
}

int AnalogInput::getRaw(){
    return analogRead(_pin);

}

float AnalogInput::getValue(){

  float inMin = 0.0;
  float inMax = 1023.0;

  //calculate for EMA filter
  float facCurrent = _dataParam.alfaEma/100.0;
  float facPrev = (100.0 - _dataParam.alfaEma)/100.0;
  int raw = this->getRaw();

  float tempVal = raw * facCurrent + facPrev * _prevVal;

  //convert to unit
  float valUnit = (tempVal - inMin) * (_dataParam.highRange - _dataParam.lowRange) / (inMax - inMin) + _dataParam.lowRange;

  //report by exception
  if (_prevVal != valUnit){
    _prevVal = valUnit;
    _exception = LOCAL_OPERATION_EXCEPTION;

    Serial.print("valUnit : ");
    Serial.println(valUnit);

  }
  return valUnit;
}

int AnalogInput::getStatus(){
  int statusAi = NO_ALARM;

  float valUnit = this->getValue();

  if (valUnit >= _dataParam.highLimit)statusAi = HIGH_ALARM;
  //else if (valUnit <= _dataParam.lowLimit)statusAi = LOW_ALARM;

  if (_prevState != statusAi){
    _prevState = statusAi;

    Serial.print("statusAi : ");
    Serial.println(statusAi);
  }

  return statusAi;
}

int AnalogInput::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void AnalogInput::info(){

  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_device : ");
  Serial.println(_device);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("PullUp : ");
  Serial.println(_pullUp);

  Serial.print("getRaw() : ");
  Serial.println(this->getRaw());

  Serial.println("");
}

