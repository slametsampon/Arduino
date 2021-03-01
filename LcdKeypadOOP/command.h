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
const char NO_KEY = 'N';//No Key pressed
const char UP = 'U';//Up Key pressed
const char DOWN = 'D';//Down Key pressed
const char RIGHT = 'R';//Right Key pressed
const char LEFT = 'L';//Left Key pressed
const char SELECT = 'S';//Select Key pressed

class command{
  public:    
    virtual char ambilCode();
    bool isValid(char);
};

class serialCmd : public command{
  public:
    serialCmd(String);
    char ambilCode();
  private:
    String  _id;    
    char  _cmd;    
};//end class

class bluetoothCmd : public command{
  public:
    bluetoothCmd(String);
    virtual char ambilCode();
  private:
    char  _cmd;
    String  _id;    
};//end class

#endif
