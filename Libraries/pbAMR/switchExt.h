/*
  switchExt.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

#ifndef switchExt_h
#define switchExt_h

#include "Arduino.h"

    //master/base class
    class Device{
        public:
            virtual void init();
            virtual boolean isStatus(unsigned long);
        private:
    };

    class SwitchExt : public Device{
        public: 
            SwitchExt(char pin);   
            void init();
            boolean isStatus(unsigned long);
        private:
            char  _pin;
            unsigned long  _prevMilli;
    };
#endif
