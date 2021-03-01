#ifndef Comparator_h
#define Comparator_h

#include "Arduino.h"

#define EQUAL   	    0	//Equal function
#define HYSTERISYS	    1	//Hysterisys function
#define LESS_THAN	    2	//Less than function
#define GREATER_THAN	3	//Greather function

class Comparator
{
  public:
    Comparator(String);
    void init();
    void setUnit(String);
    void setHigh(float);
    void setLow(float);
    void setFunction(char);
    String getId();
    String getUnit();
    char getFunction();
    bool execute(float);
    float getHigh();
    float getLow();
    unsigned char getErr();
  private:
    String _id;
    String _unit;
    unsigned char _pin;
    unsigned char _Err;
    float _setHigh;
    float _setLow;
    char _funcType;
    bool _prevSts;
};
#endif