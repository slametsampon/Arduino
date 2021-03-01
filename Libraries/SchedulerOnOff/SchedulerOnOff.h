/*
  SchedulerOnOff.h - Library untuk Proteksi Relay
  Dibuat Oleh : Sam May 2017
*/
#ifndef SchedulerOnOff_h
#define SchedulerOnOff_h
#include "Arduino.h"

#define DEFAULT_RUN_CYCLE 255  //Mili detik
#define MAX_MILLI 0xFFFFFFFF  //unsigned long 32 bits (4 bytes)
#define ONESHOOT_TYPE 0
#define CYCLYC_TYPE 1

class SchedulerOnOff
{
  private:
    byte _modeType,_runCycle;
    boolean _active,_flRun,_status,_1stRun;
    unsigned long _periodeTime,_periodeHour,_periodeMinute,_periodeSecond;
    unsigned long _initialStartTime,_initialStartHour,_initialStartMinute,_initialStartSecond;
    unsigned long _durationOn,_durationOnHour,_durationOnMinute,_durationOnSecond;
    unsigned long _prevMilli,_currMilli,_prevExeMilli,_startCycle,_TimeAccOn,_TimeAccOff;//mili detik
    
    unsigned long calculateMilliSecond(unsigned long valS,unsigned long valM,unsigned long valH);
  // Constructor - creates a SchedulerOnOff 
  // and initializes the member variables and state
  public:
    SchedulerOnOff(byte val);
    boolean isFlRun();
    void setActive(boolean val);
    byte isActive();
    boolean execute();
    void setRunCycle(unsigned int val);
    unsigned int getRunCycle();

    void setPeriodeHour(unsigned long val);
    void setPeriodeMinute(unsigned long val);
    void setPeriodeSecond(unsigned long val);
    unsigned long getPeriodeTime();

    void setInitialStartHour(unsigned long val);
    void setInitialStartMinute(unsigned long val);
    void setInitialStartSecond(unsigned long val);
    unsigned long getInitialStartTime();

    void setDurationOnHour(unsigned long val);
    void setDurationOnMinute(unsigned long val);
    void setDurationOnSecond(unsigned long val);
    unsigned long getDurationOn();
};


#endif