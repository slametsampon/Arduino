/*
  drvCmd.h - Library untuk drvCmd
  Dibuat Oleh : Sam May 2020
  Modified by : Sam Feb 17, 2021
*/
#ifndef drvCmd_h
#define drvCmd_h

    #include <Arduino.h>
    typedef void (*CallBackFunction) ();

    class drvCmd{
    public:    
        virtual void init();//Initialization
        virtual void info();
        virtual char getCmd();
        virtual void move(char);
        virtual void move(char, unsigned long);
        virtual void moveCallBack(char, unsigned long, CallBackFunction callback);
        virtual boolean isMoveable();
    };

#endif
