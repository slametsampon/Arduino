/*
  controller.h - Library untuk controller
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021

*/

#ifndef controller_h
#define controller_h

#include    "Arduino.h"
#include    "src\global\robotConstOOP.h"
#include    "src\model\model.h"
#include    "mobileRobot.h"

class Controller
{
  public:

    Controller(String);//constructor
    void init();
    void info();
    void attachMobileRobot(MobileRobot*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachGymRecord(AccessCmdRecord*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachTrackRecord(AccessCmdRecord*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachModelParameter(AccessParam*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    int getException();
    void updateParameter();
    void execute(int);
    void serialShowOperationMode();
    String getOperationMode();

  private:

    String _id, _operationModeStr;
    int _exception = NO_EXCEPTION;
    int _operationMode = MODE_LOCAL;
    int _gymStep=0;

    AccessCmdRecord *_accessGymRecord, *_accessTrackRecord;
    AccessParam *_accessParameter;
    cmdRobot *_prevCmd;
    MobileRobot *_mobileRobot;
    param _dataParam;

    void _initGym();
    void _modeGym();
};//end of class

#endif