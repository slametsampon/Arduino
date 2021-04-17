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
        virtual void init(String);//Initialization
        virtual void info();
        virtual void status();
        virtual void move(char);
        virtual void move(char, int);
    };

#endif
