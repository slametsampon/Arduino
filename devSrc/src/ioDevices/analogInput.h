/*
  analogInput.h - Library AI
  with AlfaEma filter
  By : Sam April 03, 2021
*/

#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"
#include "ioDevicesConst.h"
#include "..\model\model.h"
#include "..\global\arduinoUnoConst.h"

    class AnalogInput{
        public: 
            AnalogInput(int pin);   
            void init(boolean);
            void init(boolean, String);
            int getRaw();
            float getValue();
            int getStatus();
            int getException();
            void setParam(param);
            void info();
        private:
            int _exception = NO_EXCEPTION;
            int  _pin, _prevState;
            float _prevVal;
            String  _id, _device;
            boolean _pullUp;
            param _dataParam;
    };
#endif
