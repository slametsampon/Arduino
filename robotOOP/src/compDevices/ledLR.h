/*
  ledLR.h - Library for LED Left, Right
  By : Sam April 17, 2021

    const char MOTOR_STOP led off
    const char MOTOR_FORWARD led on
    const char MOTOR_BACKWARD led blink
*/

#ifndef ledLR_h
#define ledLR_h

//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "..\ioDevices\DigitalOutput.h"
#include "..\global\robotConstOOP.h"

    class LedLR{
        public:
            LedLR(DigitalOutput *ledLeft, DigitalOutput *ledRight):
            _ledLeft(ledLeft), _ledRight(ledRight){}
            
            void status(char leftMotor, char rightMotor){

                //left led
                switch (leftMotor){
                    case MOTOR_STOP:
                        _ledLeft->off();
                        break;
                    
                    case MOTOR_FORWARD:
                        _ledLeft->on();
                        break;
                    
                    case MOTOR_BACKWARD:
                        _ledLeft->blink(BLINK_WARNING);
                        break;
                    
                    default:
                        break;
                }

                //right led
                switch (rightMotor){
                    case MOTOR_STOP:
                        _ledRight->off();
                        break;
                    
                    case MOTOR_FORWARD:
                        _ledRight->on();
                        break;
                    
                    case MOTOR_BACKWARD:
                        _ledRight->blink(BLINK_WARNING);
                        break;
                    
                    default:
                        break;
                }
            }

            void init(){
                //initialization LEDs
                _ledLeft->init(FORWARD_TYPE,"_ledLeft");
                _ledRight->init(FORWARD_TYPE,"_ledRight");
                
            }

            void  info(){
                Serial.println("LedLR::info()");

                _ledLeft->info();
                _ledRight->info();                
                
                Serial.println(" ");
            }
        private:
            DigitalOutput *_ledLeft, *_ledRight;
    };

#endif
