/*
  ledAMR.h - Library for LED Auto, Manual, Reset
  By : Sam March 01, 2021

  1. MODE_READY = all LED off
  2. MODE_AUTO = LED Auto on, others off
  3. MODE_MANUAL = LED Manual on, others off
  4. MODE_MANUAL_ON = LED Manual blink, others off
  5. MODE_RESET = LED Reset on, others off
*/

#ifndef ledAMR_h
#define ledAMR_h

//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "..\ioDevices\DigitalOutput.h"
#include "..\global\robotOOP.h"

    class LedAMR{
        public:
            LedAMR(DigitalOutput *ledAuto, DigitalOutput *ledManual, DigitalOutput *ledReset): _ledAuto(ledAuto), _ledManual(ledManual), _ledReset(ledReset){}
            
            void status(int state){
                switch (state){
                    case MODE_TEST:
                        _ledAuto->on();
                        _ledManual->on();
                        _ledReset->on();
                        break;
                    
                    case MODE_AUTO:
                        _ledAuto->on();
                        _ledManual->off();
                        _ledReset->off();
                        break;
                    
                    case MODE_AUTO_ON:
                        _ledAuto->blink(BLINK_WARNING);
                        _ledManual->off();
                        _ledReset->off();
                        break;
                    
                    case MODE_MANUAL:
                        _ledAuto->off();
                        _ledManual->on();
                        _ledReset->off();
                        break;
                    
                    case MODE_MANUAL_ON:
                        _ledAuto->off();
                        _ledManual->blink(BLINK_WARNING);
                        _ledReset->off();
                        break;
                    
                    case MODE_READY:
                        _ledAuto->blink(BLINK_NORMAL);
                        _ledManual->blink(BLINK_NORMAL);
                        _ledReset->off();
                        break;
                    
                    case MODE_RESET:
                        _ledAuto->off();
                        _ledManual->off();
                        _ledReset->blink(BLINK_WARNING);
                        break;
                    
                    default:
                        break;
                }
            }

            void init(){
                //initialization LEDs
                _ledAuto->init(FORWARD_TYPE,"_ledAuto");
                _ledManual->init(FORWARD_TYPE,"_ledManual");
                _ledReset->init(FORWARD_TYPE,"_ledReset");
                
            }

            void  info(){
                Serial.println("LedAMR::info()");

                _ledAuto->info();
                _ledManual->info();                
                _ledReset->info();
                
                Serial.println("<----->");
            }
        private:
            DigitalOutput *_ledAuto, *_ledManual, *_ledReset;
    };

#endif
