#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

#define   GREEN_UTARA           10 //Pin LED RED_UTARA
#define   YELLOW_UTARA          11 //Pin LED YELLOW_UTARA
#define   RED_UTARA             12 //Pin LED YELLOW_UTARA
#define   GROUND_UTARA          13 //Pin LED GROUND_UTARA

#define   PIN_LED_LIVE          13 //LED blink
#define   GREEN_TIMUR           2 //Pin LED RED_TIMUR
#define   YELLOW_TIMUR          3 //Pin LED YELLOW_TIMUR
#define   RED_TIMUR             4 //Pin LED YELLOW_TIMUR
#define   GROUND_TIMUR          5 //Pin LED GROUND_TIMUR

#define   GREEN_BARAT           A3 //Pin LED RED_BARAT
#define   YELLOW_BARAT          A2 //Pin LED YELLOW_BARAT
#define   RED_BARAT             A1 //Pin LED YELLOW_BARAT
#define   GROUND_BARAT          A0 //Pin LED GROUND_BARAT

#define   BLINK_TIME            500 //Mili second
#define   RTC_SAMPLING          5000 //Mili second, RTC sampling periode
#define   DS3231_POS            A3 //Module RTC DS3231 Positive
#define   DS3231_NEG            A2 //Module RTC DS3231 Negative 
#define   BAUD_RATE             9600 //Baud rate Bluetooth bps
