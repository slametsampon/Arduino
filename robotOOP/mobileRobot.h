/*
  mobileRobot.h - Library untuk mobileRobot
  Dibuat Oleh : Sam April 15, 2021
*/
#ifndef mobileRobot_h
#define mobileRobot_h

    #include <Arduino.h>
    #include "src\compDevices\drvCmd.h"
    #include "src\compDevices\motor.h"
    #include "src\global\robotConstOOP.h"

    typedef void (*CallBackFunction) ();

    const int MAX_GEAR = 5;

    //For cmd constants
    const char CMD_FORWARD = 'F';
    const char CMD_BACKWARD = 'B';
    const char CMD_TURN_RIGHT = 'R';
    const char CMD_TURN_LEFT = 'L';
    const char CMD_STOP = 'S';
    const char CMD_UP = 'U';
    const char CMD_DOWN = 'D';
    const char CMD_AROUND_LEFT = 'I';
    const char CMD_AROUND_RIGHT = 'O';

    const char NO_CMD = 'N';

    class MobileRobot : public drvCmd{
        public: 
            MobileRobot(String);
            void init(String);//Initialization
            void info();
            void move(int);
            void move(int, int);

            void move(int, int, unsigned long);//just one shoot
            void move(int, int, unsigned long, CallBackFunction callback);
            void reset();

            void attachMotor(Motor*, Motor*);


        private:
            String _device, _id;
            int _gear;
            unsigned long _prevMs;
            boolean _canMove, _isMoving;

            Motor *_motorLeft, *_motorRight;

            static void fakeCallback();
            int _setSpeed(int);
    };

#endif
