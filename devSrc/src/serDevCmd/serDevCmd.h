/*
  command.h - Library untuk command
  Dibuat Oleh : Sam May 2020
  Modified by : Sam Feb 17, 2021
*/
#ifndef serDevCmd_h
#define serDevCmd_h

#include "Arduino.h"
#include    "..\command\command.h"

class serialCmd : public command{
  public:
    serialCmd(String);
    void init();//Initialization
    void info();
    bool isValid(char);
    char getCode();
  private:
    String  _id;    
    char  _cmd;    
};//end class

class bluetoothCmd : public command{
  public:
    bluetoothCmd(String);
    void init();//Initialization
    void info();
    virtual char getCode();
    bool isValid(char);
  private:
    char  _cmd;
    String  _id;    
};//end class

#endif
