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

class Controller
{
  public:

    Controller(String);//constructor
    void init();
    void info();
    void attachGymRecord(AccessCmdRecord*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachTrackRecord(AccessCmdRecord*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    int getException();
    void execute(int);

  private:

    String _id;
    int _exception = NO_EXCEPTION;
    int _operationMode = MODE_LOCAL;

    AccessCmdRecord *_accessGymRecord, *_accessTrackRecord;

    void _initGym();
};//end of class

#endif