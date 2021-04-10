/*
  dipAddr.h - Library for Addressing
  Addres  :
    0. 000
    1. 001
    .....
    7. 111
  By : Sam March 18, 2021
*/

#ifndef dipAddr_h
#define dipAddr_h

#include "Arduino.h"
#include "..\ioDevices\digitalInput.h"

    class DipAddr{
        public:
            DipAddr(DigitalInput*, DigitalInput*, DigitalInput*);
            int getAddr();
            void init();
            void info();
        private:
            DigitalInput *_addr0, *_addr1, *_addr2;
    };

#endif
