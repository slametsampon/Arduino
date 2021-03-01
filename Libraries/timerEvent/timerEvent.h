/*
  timerEvent.h - Library untuk Sequence timerEvent
  Dibuat Oleh : sam April 2020
*/
#ifndef timerEvent_h
#define timerEvent_h

#include "Arduino.h"

class timerEvent{
  public:
    timerEvent(bool);
    void setTimer(unsigned long);
    unsigned long getTimer();
    unsigned long getRemain();
    bool run();
    bool isActive();
    void setActive(bool);
  private:
    unsigned long _setTimer, _prevMilli, _remainMilli;
    bool _isActive;
};

#endif