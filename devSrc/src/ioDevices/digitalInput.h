/*
  digitalInput.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

#ifndef digitalInput_h
#define digitalInput_h

#include "Arduino.h"
#include "ioDevicesConst.h"

    class DigitalInput{
        public: 
            DigitalInput(int pin);   
            void init(boolean);
            void init(boolean, String);
            boolean isStatus(unsigned long);
            boolean isStatus();
            void info();
        private:
            int  _pin;
            unsigned long  _prevMilli;
            String  _id, _device;
            boolean _digTyp = REVERSE_TYPE;
            boolean _prevStatus, _isFirst;
    };
#endif
