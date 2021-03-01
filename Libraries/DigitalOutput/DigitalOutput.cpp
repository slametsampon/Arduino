/*
 * lihat header file DigitalOutput.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "DigitalOutput.h"

//Constructor class c/w initialization
DigitalOutput::DigitalOutput(char pin):_pin(pin){}

void DigitalOutput::init(){
  pinMode(_pin, OUTPUT);
}

char DigitalOutput::getPin(){
  return _pin;
}

void DigitalOutput::setOff(){//low level untuk drive aktif relay
  digitalWrite(_pin, HIGH);
}

void DigitalOutput::setOn(){//high level untuk drive open relay
  digitalWrite(_pin, LOW);
}

void DigitalOutput::blink(unsigned long blinkTime){
  if ((millis() - _prevMilli) >= blinkTime){
    _prevMilli = millis();
    digitalWrite( _pin, digitalRead(_pin) ^ 1 );
  }
}

void DigitalOutput::setOnFor(unsigned long msVal){
  if (_prevMilli == 0){
    _prevMilli = millis();
    isBusy  = true;
    DigitalOutput::setOn();
  }
  if ((millis() - _prevMilli) >= msVal){
    DigitalOutput::setOff();
    _prevMilli = 0;
    isBusy = false;
  }
}

boolean DigitalOutput::isRunning(){
  return isBusy;
}
