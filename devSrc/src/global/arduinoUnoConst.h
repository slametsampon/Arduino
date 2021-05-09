/*
All constants for local panel
*/

#ifndef arduinoUnoConst_h
#define arduinoUnoConst_h

    //#define PIN_KEYPAD A0 // pin Analog Keypad
    const int PIN_KEYPAD        = A0;//pin Analog Keypad
    const int PIN_SENSOR        = A1;//pin Analog fire sensor

    const int LCD_RS            = 8;
    const int LCD_EN            = 9;
    const int LCD_D4            = 4;
    const int LCD_D5            = 5;
    const int LCD_D6            = 6;
    const int LCD_D7            = 7;

    const int BLINK_NORMAL = 500;//milli second
    const int BLINK_WARNING = 250;//milli second
    const int BLINK_ERROR = 125;//milli second

    //menu status
    const int MAX_MENU = 3;
    const int MODE_MENU_MAIN = 1;
    const int MODE_MENU_PARAMETER = 2;
    const int MODE_CHANGE_PARAMETER = 3;
    const int DEFAULT_INDEX = 999;

    //Operation mode
    const int MODE_READY = 0;
    const int MODE_AUTO = 1;
    const int MODE_AUTO_ON = 2;
    const int MODE_MANUAL = 3;
    const int MODE_MANUAL_ON = 4;
    const int MODE_RESET = 5;
    const int MODE_TEST = 99;

    //Exception code
    const int NO_EXCEPTION = 0;
    const int LOCAL_OPERATION_EXCEPTION = 1;//change on value or operation mode
    const int LOCAL_PARAMETER_EXCEPTION = 2;//change on parameter
    const int REMOTE_OPERATION_EXCEPTION = 3;//change on value or operation mode remotely
    const int REMOTE_PARAMETER_EXCEPTION = 4;//change on parameter remotely

    const int ADC_MAX = 1023;//10 bits
    const int ALFA_EMA = 80;//AlfaEma filter
    const int DEBOUNCING_TIME = 150;//milli second

#endif
