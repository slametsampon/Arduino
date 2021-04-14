/*
  mobileRobot.h - Library untuk mobileRobot
  Dibuat Oleh : Sam April 15, 2021
*/
#ifndef mobileRobot_h
#define mobileRobot_h

    #include <Arduino.h>
    #include <L298N.h>
    #include "src\compDevices\drvCmd.h"
    #include "src\global\robotConstOOP.h"

    typedef void (*CallBackFunction) ();

    const char MAX_DRIVE = 4;//Maximum Input mobileRobot devices
    const char STOP_BT = '%';//Stop Bluetooth mobileRobot

    //For cmd constants
    const char FORWARD_CMD = 'F';
    const char BACK_CMD = 'B';
    const char TURN_RIGHT_CMD = 'R';
    const char TURN_LEFT_CMD = 'L';
    const char STOP_CMD = 'S';
    const char UP_CMD = 'U';
    const char DOWN_CMD = 'D';

    const char NO_CMD = 'N';

    class MobileRobot : public drvCmd{
        public:    
            void init();//Initialization
            void info();
            char getCmd();
            void move(char);
            void move(char, unsigned long);
            void moveCallBack(char, unsigned long, CallBackFunction callback);
            boolean isMoveable();

            void attachDrive(drvCmd*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)

        private:
            L298N *_drive[MAX_DRIVE];

    };

#endif
