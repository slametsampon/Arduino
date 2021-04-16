/*
  motor.h - Library untuk motor
  Dibuat Oleh : Sam April 15, 2021
*/
#ifndef motor_h
#define motor_h

    #include <Arduino.h>
    #include "drvCmd.h"

    typedef void (*CallBackFunction) ();

    const int MOTOR_STOP = 0;
    const int MOTOR_FORWARD = 1;
    const int MOTOR_BACKWARD = 2;
    const int MAX_PWM = 255;

    class Motor : public drvCmd{
        public:
            Motor(int, int, int);    
            void init(String);//Initialization
            void info();
            void move(int);//move full speed
            void move(int, int);

        private:
            String _device, _id;
            int _cmd, _pinEnable, _pinIN1, _pinIN2, _pwmVal;

            void _stop();
            void _forward();
            void _backward();
    };

#endif
