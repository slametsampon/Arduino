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

const char PB_READY = 0;
const char PB_AUTO = 1;
const char PB_MANUAL = 2;
const char PB_MANUAL_ON = 3;
const char PB_RESET = 4;
const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "switchExt.h"
    class PbAMR{
        public:
            PbAMR(switchExt*, switchExt*, switchExt*);
            char getCmd();
            void info();
        private:
            switchExt *_pbAuto, *_pbManual, *_pbReset;
            char    _prevCmd;
    };

#endif
