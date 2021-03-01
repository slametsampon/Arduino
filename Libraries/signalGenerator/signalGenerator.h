/*
  RelayProt.h - Library untuk Proteksi Relay
  Dibuat Oleh : Abi May 2017
*/
#ifndef signalGenerator_h
#define signalGenerator_h
#include "Arduino.h"

#define DEFAULT_RUN_CYCLE 255  //Mili detik
#define NONE_TYPE 0
#define RANDOM_TYPE 1
#define SIN_TYPE 2
#define COS_TYPE 3
#define TRIANGLE_TYPE 4
#define SAWTOOTH_TYPE 5
#define SQUARE_TYPE 6
class signalGenerator
{
  private:
    byte _signalType,_runCycle;
    boolean _active,_flRun;
    unsigned long _periodTime,_prevMilli,_prevMilliSegi3,_prevMilliSaw,_startCycle;//mili detik
    byte  _percentCycle,_valueRaw;
    float _minValue,_maxValue,_value,_phaseShift;
    float calculateValue();
    float signalRandom();
    float signalCosinus();
    float signalSinus();
    float signalSquare();
    float signalTriangle();
    float signalSawTooth();
  public:
    signalGenerator(byte val);
    boolean isFlRun();
    float execute();
    void setRunCycle(byte val);
    byte getRunCycle();
    float getValue();
    byte getValueRaw();
    float getPhaseShift();
    void setPhaseShift(float val);
    void setPeriodTime(unsigned long val);
    unsigned long getPeriodTime();
    void setMaxValue(float val);
    float getMaxValue();
    void setMinValue(float val);
    float getMinValue();
    void setSignalType(byte val);
    byte getSignalType();
    void setPercentCycle(byte val);
    byte getPercentCycle();
    void setActive(boolean val);
    byte isActive();
};
#endif
