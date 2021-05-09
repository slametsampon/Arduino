/*
  digitalOutput.h - Library for Digital Output (DO)
  Digital Input with debouncing mechanism 
  By : Sam March 03, 2021
*/

#ifndef DigitalOutput_h
#define DigitalOutput_h

#include "Arduino.h"
#include "ioDevicesConst.h"

  class DigitalOutput{
    public: 
      //constructor
      DigitalOutput(int pin);  

      void init(boolean);
      void init(String);
      void init(boolean, String);
      boolean isStatus();
      void info();

      //typical for DO
      void on();
      void off();
      void blink(unsigned long);
    private:
      int  _pin;
      boolean _actionType;
      String _id, _device;
      unsigned long  _prevMilli;//in milli second
  };
#endif
