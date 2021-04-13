/*
  drvCmd.h - Library untuk drvCmd
  Dibuat Oleh : Sam May 2020
  Modified by : Sam Feb 17, 2021
*/
#ifndef drvCmd_h
#define drvCmd_h

    #include <Arduino.h>

    const char MAX_CMD_INPUT = 4;//Maximum Input drvCmd devices
    const char STOP_BT = '%';//Stop Bluetooth drvCmd

    //For cmd constants
    const char FORWARD_CMD = 'F';
    const char BACK_CMD = 'B';
    const char TURN_RIGHT_CMD = 'R';
    const char TURN_LEFT_CMD = 'L';
    const char STOP_CMD = 'S';
    const char UP_CMD = 'U';
    const char DOWN_CMD = 'D';

    const char NO_CMD = 'N';

    class drvCmd{
    public:    
        virtual void init();//Initialization
        virtual void info();
        virtual char getCmd();
        virtual void move(char);
        virtual void move(char, unsigned long);
        virtual void moveCallBack(char, unsigned long);
        virtual boolean isMoveable();
    };

#endif
