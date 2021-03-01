/*
  DigitalInput.h - Library untuk DigitalInput
  Dibuat Oleh : Sam May 2020
*/
#ifndef DigitalInput_h
#define DigitalInput_h

#include "Arduino.h"

class DEVICE{
  public:
    virtual void init();
    virtual char getPin();
  private:
};
class DigitalInput : public DEVICE{
  public: 
    DigitalInput(char pin);   
    void init();
    char getPin();
    void setSimulate(bool);
    bool isSimulate();
    bool getPV();
    bool getPV(unsigned long);
  private:
    char  _pin;
    unsigned long  _prevMilli;
    bool _transStatus;
    bool _isSimulate, _valSimulate;    
};
#endif
