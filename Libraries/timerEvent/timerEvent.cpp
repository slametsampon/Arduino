#include "timerEvent.h"

timerEvent::timerEvent(bool val):_isActive(val){}

void timerEvent::setTimer(unsigned long val){
    _setTimer = val;
    _prevMilli = 0;
}

unsigned long timerEvent::getTimer(){
    return _setTimer;
}

unsigned long timerEvent::getRemain(){
    return _remainMilli;
}

bool timerEvent::isActive(){
    return _isActive;
}

void timerEvent::setActive(bool val){
    _isActive = val;
}

bool timerEvent::run(){
    bool isEvent = false;
    if (isActive){
        if(_prevMilli == 0){
            _prevMilli = millis();
        }
        else{
            _remainMilli = _setTimer - (millis()-_prevMilli);//count down
            if(_remainMilli <= 0){
                _prevMilli = 0;
                isEvent = true;
            }
        }
    }
    return isEvent;
}