/*
  PbAutoManualStop.h - Library untuk PbAutoManualStop
  Dibuat Oleh : Sam May 2020
*/
#ifndef PbAutoManualStop_h
#define PbAutoManualStop_h

//Kode Perintah
#define   CMD_NONE          0 //Command None 
#define   CMD_AUTO          1 //Command Auto
#define   CMD_MANUAL        2 //Command Manual
#define   CMD_STOP          3 //Command Stop

#include "Arduino.h"

class PbAutoManualStop{
  public: 
    PbAutoManualStop(String);   
    void init();
    char getCmd(bool, bool, bool);
    String getId();
  private:
    bool _pbAuto, _pbManual, _pbStop;
    char _prevCmd;
    String _id;
};
#endif
