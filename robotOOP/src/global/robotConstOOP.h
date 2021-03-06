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
    const int MAIN_MODE_EXCEPTION = 1;
    const int LOCAL_MODE_EXCEPTION = 2;
    const int REMOTE_MODE_EXCEPTION = 3;
    const int GYM_MODE_EXCEPTION = 4;
    const int LINE_TRACER_MODE_EXCEPTION = 5;
    const int AVOIDER_MODE_EXCEPTION = 6;
    const int REMOTE_PARAMETER_EXCEPTION = 7;
    const int LOCAL_PARAMETER_EXCEPTION = 8;

    //menu status
    const int DEFAULT_INDEX = 999;
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

    const char MOBILE_LOCAL = 'C';
    const char MOBILE_REMOTE = 'M';
    const char MOBILE_LINE_TRACER = 'T';
    const char MOBILE_AVOIDER = 'V';
    const char MOBILE_GYM = 'G';

    const char NO_CMD = 'N';

#endif
