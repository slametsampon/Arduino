/*
  pbAMR.h - Library for Push Button Auto, Manual, Reset
  Priority :
    1. Reset
    2. Manual
    3. Auto
  By : Sam March 01, 2021
*/

#ifndef pbAMR_h
#define pbAMR_h

//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "..\ioDevices\digitalInput.h"
#include "..\global\robotOOP.h"

    class PbAMR{
        public:
            PbAMR(DigitalInput*, DigitalInput*, DigitalInput*);
            int getCmd(unsigned long);
            int getException();
            void init();
            void info();
        private:
            DigitalInput *_pbAuto, *_pbManual, *_pbReset;
            int    _prevCmd;
            bool  _isInfo;//one shoot info
            void _status();
            int _exception = NO_EXCEPTION;
    };

#endif
