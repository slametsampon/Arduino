/*
  command.h - Library untuk command
  Dibuat Oleh : Sam May 2020
  Modified by : Sam Feb 17, 2021
*/
#ifndef command_h
#define command_h

#include "Arduino.h"

const char MAX_CMD_INPUT = 4;//Maximum Input command devices
const char STOP_BT = '%';//Stop Bluetooth Command
//For Keypad constants
const char UP = 'U';//Up Key pressed
const char DOWN = 'D';//Down Key pressed
const char RIGHT = 'R';//Right Key pressed
const char LEFT = 'L';//Left Key pressed
const char SELECT = 'S';//Select Key pressed

const char NO_KEY = 'N';//No Key pressed

class command{
  public:    
    virtual void init();//Initialization
    virtual void info();
    virtual char getCode();
    virtual bool isValid(char);
};

#endif
