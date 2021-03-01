/*
  KeyPad.h - Library untuk AnalogInput
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef KeyPad_h
#define KeyPad_h

#include "Arduino.h"
#include "command.h"

const int DEBOUNCE_DELAY = 100;//milli second

class KeyPad : public command{
  public:
    KeyPad(int);//constructor
    void Init();//Initialization
    int ambilNilai();//function for getting keypad value
    char ambilCode();//Convert keypad value to char
  private:
    int _pinAnalog;
    unsigned long _prevMilli;
    char _prevKey;
};//end of class
#endif
