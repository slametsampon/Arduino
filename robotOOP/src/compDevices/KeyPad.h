/*
  keyPad.h - Library untuk keyPad
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef keyPad_h
#define keyPad_h

#include "Arduino.h"
#include "..\command\command.h"
#include "..\ioDevices\analogInput.h"

const int DEBOUNCE_DELAY = 150;//milli second
const int VALUE_RIGHT = 60;
const int VALUE_UP = 200;
const int VALUE_DOWN = 400;
const int VALUE_LEFT = 600;
const int VALUE_SELECT = 800;

class KeyPad : public command{
  public:
    KeyPad(AnalogInput*);//constructor
    void init();//Initialization
    bool isValid(char);
    void info();
    char getCode();//Convert keypad value to char

    int getValue();//function for getting keypad value
  private:
    AnalogInput *_analogInput;
    unsigned long _prevMilli;
    char _prevKey;
};//end of class
#endif
