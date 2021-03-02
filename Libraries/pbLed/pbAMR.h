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

const char STATUS_READY = 0;
const char STATUS_AUTO = 1;
const char STATUS_MANUAL = 2;
const char STATUS_MANUAL_ON = 3;
const char STATUS_RESET = 4;
//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "switchExt.h"

    class PbAMR{
        public:
            PbAMR(SwitchExt*, SwitchExt*, SwitchExt*);
            char getCmd(unsigned long);
            void info();
        private:
            SwitchExt *_pbAuto, *_pbManual, *_pbReset;
            char    _prevCmd;
            bool  _isInfo;//one shoot info
    };

#endif
