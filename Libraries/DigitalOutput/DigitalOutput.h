/*
  DigitalOutput.h - Library untuk DigitalOutput
  Dibuat Oleh : Sam May 2020
*/
#ifndef DigitalOutput_h
#define DigitalOutput_h

#include "Arduino.h"

class DEVICE{
  public:
    virtual void init();
    virtual char getPin();
  private:
};
class DigitalOutput : public DEVICE{
  public:
    DigitalOutput(char pin);
    void init();
    char getPin();
    void setOn();
    void setOff();
    void blink(unsigned long);
    void setOnFor(unsigned long);
    bool isRunning();
   
  private:
    unsigned long  _prevMilli;
    char  _pin;
    bool isBusy;
};
#endif

