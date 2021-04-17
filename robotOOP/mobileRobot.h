/*
  mobileRobot.h - Library untuk mobileRobot
  Dibuat Oleh : Sam April 15, 2021
*/
#ifndef mobileRobot_h
#define mobileRobot_h

    #include <Arduino.h>
    #include "src\compDevices\drvCmd.h"
    #include "src\compDevices\motor.h"
    #include "src\compDevices\ledLR.h"
    #include "src\global\robotConstOOP.h"

    typedef void (*CallBackFunction) ();

    const int MAX_GEAR = 5;

    //For cmd constants
    const char MOBILE_FORWARD = 'F';
    const char MOBILE_BACKWARD = 'B';
    const char MOBILE_TURN_RIGHT = 'R';
    const char MOBILE_TURN_LEFT = 'L';
    const char MOBILE_STOP = 'S';
    const char MOBILE_UP = 'U';
    const char MOBILE_DOWN = 'D';
    const char MOBILE_AROUND_LEFT = 'I';
    const char MOBILE_AROUND_RIGHT = 'O';

    const char NO_CMD = 'N';

    class MobileRobot : public drvCmd{
        public: 
            MobileRobot(String);
            void init();//Initialization
            void init(String);//Initialization
            void info();
            void status();
            void move(char);
            void move(char, int);

            void move(char, int, unsigned long);//just one shoot
            void move(char, int, unsigned long, CallBackFunction callback);
            void reset();

            void attachMotor(Motor*, Motor*);
            void attachLedLR(LedLR*);//led Left and Right

        private:
            String _device, _id, _cmdStr;
            int _gear;
            unsigned long _prevMs;
            boolean _isMoveable, _isMoving;
            char _cmd;

            Motor *_motorLeft, *_motorRight;
            LedLR *_ledLR;

            static void fakeCallback();
            int _setSpeed(int);
    };

#endif
