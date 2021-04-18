/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON

*/
#ifndef model_h
#define model_h

  #include "Arduino.h"
  #include "..\global\robotConstOOP.h"

  typedef struct dataMenu{
    char* Messages;
  }dataMenu;

  class AccessDataMenu{
    public:
      static unsigned char menuNbr;
      static unsigned char getmenuNbr(){
        return menuNbr;
      }
      AccessDataMenu(String );
      void info();
      void add(dataMenu);
      dataMenu read(int);
    private:
      dataMenu  _dataMenu[MAX_MENU];
      String    _id;
  };//end of class

  typedef struct cmdRobot{
    char cmd;//Command
    int gear;
    unsigned long milliS;//milli second
    cmdRobot *next; 
  }cmdRobot;

  class AccessCmdRecord{
    public:
      AccessCmdRecord(String );
      void add(char, int, unsigned long);
      cmdRobot *getFirstRecord();
      void info();
      void serialShowCmdRobot(cmdRobot*);
    private:
      String    _id;
      int _nbrRecord=0;
      cmdRobot *_firstRecord, *_lastRecord;
  };//end of class

#endif
