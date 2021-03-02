/*
  switchExt.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "switchExt.h"

SwitchExt::SwitchExt(char pin):_pin(pin){}
void SwitchExt::init(){
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. 
  // HARDWARE WIRING SHOULD BE CONCERNED !!!!! 
  pinMode(_pin, INPUT_PULLUP);
}

boolean SwitchExt::isStatus(unsigned long holdTime){
  boolean validSts = false;
  //HIGH when it's open, and LOW when it's pressed. it's INPUT_PULLUP
  if (!digitalRead(_pin)){
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
