/*
  pbAMR.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

switchExt::switchExt(char pin):_pin(pin){}
void switchExt::init(){
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. 
  // HARDWARE WIRING SHOULD BE CONCERNED !!!!! 
  pinMode(_pin, INPUT_PULLUP);
}

boolean switchExt::isStatus(unsigned long holdTime){
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

PbAMR::PbAMR(switchExt *pbAuto, switchExt *pbManual, switchExt *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

char PbAMR::getCmd(){
    char cmd;
    if (_pbReset->isStatus(DEBOUNCE_PB)){
        cmd = PB_READY;//highest priority
        _prevCmd = cmd;
    }
    else {
        if(_pbAuto->isStatus(DEBOUNCE_PB)){
            cmd = PB_AUTO;//lower priority
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(DEBOUNCE_PB)){
            cmd = PB_MANUAL;//higher priority
            _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }
    return cmd;
}

void PbAMR::info(){
    switch (_prevCmd)
    {
    case PB_AUTO:
        Serial.println("PB : Auto");
        break;
    
    case PB_MANUAL:
        Serial.println("PB : Manual");
        break;
    
    case PB_READY:
        Serial.println("PB : Ready");
        break;
    
    case PB_RESET:
        Serial.println("PB : Reset");
        break;
    
    default:
        break;
    }
}