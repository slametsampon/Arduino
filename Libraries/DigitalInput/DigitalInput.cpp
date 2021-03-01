/*
 * lihat header file DigitalInput.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "DigitalInput.h"
//#include "Arduino.h"

DigitalInput::DigitalInput(char pin):_pin(pin){}
void DigitalInput::init(){
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. 
  // HARDWARE WIRING SHOULD BE CONCERNED !!!!! 
  pinMode(_pin, INPUT_PULLUP);
}

char DigitalInput::getPin(){
  return _pin;
}

boolean DigitalInput::getPV(){
    if (_isSimulate) return _valSimulate;
  //HIGH when it's open, and LOW when it's pressed. it's INPUT_PULLUP
    else return digitalRead(_pin);
}

boolean DigitalInput::isSimulate(){
    return _isSimulate;
}

void DigitalInput::setSimulate(boolean simVal){
    _isSimulate = simVal;
}

boolean DigitalInput::getPV(unsigned long holdTime){
  boolean validSts = false;
  //HIGH when it's open, and LOW when it's pressed. it's INPUT_PULLUP
  if (!DigitalInput::getPV()){
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
