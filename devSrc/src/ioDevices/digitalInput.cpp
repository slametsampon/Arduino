/*
  digitalInput.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "digitalInput.h"

DigitalInput::DigitalInput(int pin):_pin(pin), _id("DigitalInput"), _digTyp(REVERSE_TYPE){
  _device = _id;
  this->init(_digTyp);
}

void DigitalInput::init(boolean typ){
  _digTyp = typ;
  _isFirst = false;
  _prevStatus = false;

  if(_digTyp == FORWARD_TYPE)pinMode(_pin, INPUT);
  else pinMode(_pin, INPUT_PULLUP);

}

void DigitalInput::init(boolean type, String id){
  _id = id;

  this->init(type);
  }

boolean DigitalInput::isStatus(){

  boolean sts = digitalRead(_pin);
  if (!_isFirst){
    _isFirst = true;
    if(REVERSE_TYPE)return(!sts)
    else return sts;
  }
  if (sts != _prevStatus){
    _prevStatus = sts;
    Serial.print(_id);
    Serial.print(" : ");
    if (_digTyp == REVERSE_TYPE){
      if (!sts)Serial.println("Active");
      else Serial.println("Inactive");
      return (!sts);
    }
    else{
      if (sts)Serial.println("Active");
      else Serial.println("Inactive");
      return (sts);
    }
  }
}

boolean DigitalInput::isStatus(unsigned long holdTime){
  boolean validSts = false;

  if (this->isStatus()){
    if (_prevMilli == 0){
      _prevMilli = millis();//Transition for new command
    }
    else {
      if ((millis() - _prevMilli) >= holdTime){
        validSts = true;
        _prevMilli = 0;
      }
    }
  }
  return validSts;
}

void DigitalInput::info(){

  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_device : ");
  Serial.println(_device);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("Type : ");
  if (_digTyp == FORWARD_TYPE) Serial.println("FORWARD");
  else Serial.println("REVERSE");

  this->isStatus();

  Serial.println("");
}

