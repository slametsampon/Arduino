/*
  pbAMR.h - Library for P/B Auto, Manual, Reset
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(SwitchExt *pbAuto, SwitchExt *pbManual, SwitchExt *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

char PbAMR::getCmd(unsigned long debounceTime){
    char cmd;
    if (_pbReset->isStatus(debounceTime)){
      if (_prevCmd == STATUS_RESET) cmd = STATUS_READY;//highest priority
      else if (_prevCmd == STATUS_READY) cmd = STATUS_READY;//highest priority
      else cmd = STATUS_RESET;//highest priority
      if(_prevCmd != cmd) _isInfo = false;
      _prevCmd = cmd;
    }
    else {
        if((_pbAuto->isStatus(debounceTime) && (_prevCmd != STATUS_MANUAL_ON))){
            cmd = STATUS_AUTO;//lower priority
            if(_prevCmd != cmd) _isInfo = false;
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(debounceTime)){
          if (_prevCmd == STATUS_MANUAL) cmd = STATUS_MANUAL_ON;//higher priority
          else if (_prevCmd == STATUS_MANUAL_ON) cmd = STATUS_MANUAL_ON;//higher priority
          else cmd = STATUS_MANUAL;//higher priority

          if(_prevCmd != cmd) _isInfo = false;
          _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }
    return cmd;
}

void PbAMR::info(){
    if(!_isInfo){
        _isInfo = true;
        switch (_prevCmd)
        {
        case STATUS_AUTO:
            Serial.println("PB : Auto");
            break;
        
        case STATUS_MANUAL:
            Serial.println("PB : Manual");
            break;
        
        case STATUS_MANUAL_ON:
            Serial.println("PB : Manual ON");
            break;
        
        case STATUS_READY:
            Serial.println("PB : Ready");
            break;
        
        case STATUS_RESET:
            Serial.println("PB : Reset");
            break;
        
        default:
            break;
        }
    }
}