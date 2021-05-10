#ifndef Comparator_h
#define Comparator_h

#include <Arduino.h>
#include "..\model\model.h"
	#include "../ioDevices/analogInput.h"
	#include "../ioDevices/digitalOutput.h"

const int EQUAL = 0;
const int HYSTERISYS = 1;
const int LESS_THAN = 2;
const int GREATER_THAN = 3;

  class Comparator{
    public:
      Comparator(String);
      void init();
			void attachInput(AnalogInput*);
			void attachOutput(DigitalOutput*);
      void setParam(param);
      void setFunction(char);
      void info();
      boolean execute();
      boolean execute(float);
    private:
      String _id;
      String _unit;
      unsigned char _pin;
      char _funcType;
      bool _prevSts;
      param _dataParam;
  };
#endif