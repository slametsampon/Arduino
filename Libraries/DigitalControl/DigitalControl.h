#ifndef DigitalControl_h
#define DigitalControl_h

#include "Arduino.h"

#define ONE_SHOOT  	    0	//One shoot only
#define HOLD_RELEASE    1	//Hold high input up release/reset
#define TRANS_ON	    2	//Transition on
#define TRANS_OFF   	3	//Transition off

class DigitalControl
{
  public:
    DigitalControl(String);
    void init();
    void setFunction(char);
    String getId();
    char getFunction();
    void setRelease(bool);
    bool isRelease();
    bool execute(bool);
  private:
    String _id;
    char _funcType;
    bool _prevOutSts, _prevInSts, _releaseSts,_executedSts;
};
#endif