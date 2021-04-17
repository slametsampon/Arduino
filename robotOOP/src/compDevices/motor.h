/*
  motor.h - Library untuk motor
  Dibuat Oleh : Sam April 15, 2021
*/
#ifndef motor_h
#define motor_h

    #include <Arduino.h>
    #include "drvCmd.h"

    typedef void (*CallBackFunction) ();

    const char MOTOR_STOP = 'S';
    const char MOTOR_FORWARD = 'F';
    const char MOTOR_BACKWARD = 'B';
    const int MAX_PWM = 255;

    class Motor : public drvCmd{
        public:
            Motor(int, int, int);    
            void init();//Initialization
            void init(String);//Initialization
            void info();
            void status();
            char getCmd();
            void move(char);//move full speed
            void move(char, int);

        private:
            String _device, _id, _cmdStr;
            int _cmd, _pinEnable, _pinIN1, _pinIN2, _pwmVal;

            void _stop();
            void _forward();
            void _backward();
    };

#endif
