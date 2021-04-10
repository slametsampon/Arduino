/*
  pbAMR.h - Library for P/B Auto, Manual, Reset
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(DigitalInput *pbAuto, DigitalInput *pbManual, DigitalInput *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

int PbAMR::getCmd(unsigned long debounceTime){
    int cmd;
    
    if (_pbReset->isStatus(debounceTime)){
      if (_prevCmd == MODE_RESET) cmd = MODE_READY;//highest priority
      else if (_prevCmd == MODE_READY) cmd = MODE_READY;//highest priority
      else cmd = MODE_RESET;//highest priority
      if(_prevCmd != cmd) _isInfo = false;
      _prevCmd = cmd;
    }
    else {
        if((_pbAuto->isStatus(debounceTime) && (_prevCmd != MODE_MANUAL_ON))){
            cmd = MODE_AUTO;//lower priority
            if(_prevCmd != cmd) _isInfo = false;
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(debounceTime)){
          if (_prevCmd == MODE_MANUAL) cmd = MODE_MANUAL_ON;//higher priority
          else if (_prevCmd == MODE_MANUAL_ON) cmd = MODE_MANUAL_ON;//higher priority
          else cmd = MODE_MANUAL;//higher priority

          if(_prevCmd != cmd) _isInfo = false;
          _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }

    //report by exception
    if (!_isInfo)_exception = LOCAL_OPERATION_EXCEPTION;

    this->_status();
    return cmd;
}

int PbAMR::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

//init for peripherals
void PbAMR::init(){
    //initialization switch
    _pbAuto->init(REVERSE_TYPE, "_pbAuto");
    _pbManual->init(REVERSE_TYPE, "_pbManual");
    _pbReset->init(REVERSE_TYPE, "_pbReset");
}
void PbAMR::info(){
    Serial.println("PbAMRT::info()");

    _pbAuto->info();
    _pbManual->info();    
    _pbReset->info();    
    
    Serial.println("<----->");
}

void PbAMR::_status(){
    String str = "NO_PB";
    switch (_prevCmd)
    {
    case MODE_AUTO:
        str = "PB : Auto";
        break;
    
    case MODE_MANUAL:
        str = "PB : Manual";
        break;
    
    case MODE_MANUAL_ON:
        str = "PB : Manual ON";
        break;
    
    case MODE_READY:
        str = "PB : Ready";
        break;
    
    case MODE_RESET:
        str = "PB : Reset";
        break;
    
    case MODE_TEST:
        str = "PB : Test";
        break;
    
    default:
        break;
    }
    //report by exception
    if (!_isInfo){
        _isInfo = true;
        Serial.println(str);
    }
}
