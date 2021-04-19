/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON

*/
#ifndef model_h
#define model_h

  #include "Arduino.h"
  #include  <ArduinoJson.h>
  #include "..\global\robotConstOOP.h"

  const int PARAMETER_VALUE = 0;
  const int PARAMETER_LOW_RANGE = 1;
  const int PARAMETER_HIGH_RANGE = 2;
  const int PARAMETER_LOW_LIMIT = 3;
  const int PARAMETER_HIGH_LIMIT = 4;
  const int PARAMETER_ALFA_EMA = 5;
  const int PARAMETER_INCREMENT = 6;
  const int PARAMETER_ALARM = 7;
  const int PARAMETER_OPERATION_MODE = 8;
  const float DELTA_INCREMENT = 0.5;

  //commSer header code
  const int DATA_OPERATION = 0;
  const int DATA_PARAMETER = 1;
  const int REMOTE_PARAMETER = 2;
  const int REMOTE_OPERATION = 3;

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

  typedef struct param{
      String unit;//unit
      float value;
      float highRange;
      float lowRange;
      float highLimit;//for alarm high
      float lowLimit;//for alarm low
      float alfaEma;//alfa for EMA Filter (0 - 100) in percentage
      float increment;
      int alarm;
      int operationMode;
  }param;

  class AccessParam{
  
  public:
      AccessParam(String);
      void init(String, param);
      void info();
      JsonObject getJson();
      JsonObject getOperation();
      void setOperationJson(JsonObject);
      param getParam();
      void setParamJson(JsonObject);
      void setParam(param);
      void setParam(int, float);
      boolean isChangeAble(int);
      void setAlarm(int);
      String toString();
      String getId();
      void setOperationMode(int);
      int getOperationMode();

  private:
      String    _id;
      param _dataParam;
      int _operationMode;

  };//end of class
#endif
