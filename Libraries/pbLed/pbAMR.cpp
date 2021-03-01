/*
  pbAMR.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(switchExt *pbAuto, switchExt *pbManual, switchExt *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

char PbAMR::getCmd(){
    char cmd;
    if (_pbReset->isStatus(DEBOUNCE_PB)){
      if (_prevCmd == PB_RESET) cmd = PB_READY;//highest priority
      else cmd = PB_RESET;//highest priority
      _prevCmd = cmd;
    }
    else {
        if(_pbAuto->isStatus(DEBOUNCE_PB)){
            cmd = PB_AUTO;//lower priority
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(DEBOUNCE_PB)){
          if (_prevCmd == PB_MANUAL) cmd = PB_MANUAL_ON;//higher priority
          else cmd = PB_MANUAL;//higher priority
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
    
    case PB_MANUAL_ON:
        Serial.println("PB : Manual ON");
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