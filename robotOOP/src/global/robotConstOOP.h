/*
All constants for local panel
*/

#ifndef robotOOP_h
#define robotOOP_h

    //#define PIN_KEYPAD A0 // pin Analog Keypad
    const int PIN_KEYPAD        = A0;//pin Analog Keypad
    const int PIN_SENSOR        = A1;//pin Analog fire sensor

    const int LCD_RS            = 8;
    const int LCD_EN            = 9;
    const int LCD_D4            = 4;
    const int LCD_D5            = 5;
    const int LCD_D6            = 6;
    const int LCD_D7            = 7;

    const int PIN_LED_LEFT      = 52; 
    const int PIN_LED_RIGHT     = 53; 

    //drive
    const int PIN_MOTOR_LEFT_ENA    = 44; 
    const int PIN_MOTOR_LEFT_IN1    = 45; 
    const int PIN_MOTOR_LEFT_IN2    = 47; 
    const int PIN_MOTOR_RIGHT_ENB   = 46; 
    const int PIN_MOTOR_RIGHT_IN3   = 49; 
    const int PIN_MOTOR_RIGHT_IN4   = 51; 

    const int ADC_MAX = 1023;//10 bits
    const int ALFA_EMA = 80;//AlfaEma filter
    const int DEBOUNCING_TIME = 500;//milli second

    const int BLINK_NORMAL = 500;//milli second
    const int BLINK_WARNING = 250;//milli second
    const int BLINK_ERROR = 125;//milli second

    //Exception code
    const int NO_EXCEPTION = 0;
    const int LOCAL_OPERATION_EXCEPTION = 1;//change on value or operation mode
    const int LOCAL_PARAMETER_EXCEPTION = 2;//change on parameter
    const int REMOTE_OPERATION_EXCEPTION = 3;//change on value or operation mode remotely
    const int REMOTE_PARAMETER_EXCEPTION = 4;//change on parameter remotely

    //menu status
    const int DEFAULT_INDEX = 999;

    enum{     
        MODE_MAIN, //index 0    
        MODE_LOCAL, //index 1    
        MODE_REMOTE, //index 2    
        MODE_GYM, //index 3    
        MODE_LINE_TRACER, //index 4    
        MODE_AVOIDER, //index 5    
        //! leave this one
        MAX_MENU 
    };

#endif
