/*
    It is just for testing only, for usage of :
    - LedExt - LED Extended
    - SwitchExt - Switch Extended
    - PbAMR - Push button Auto, Manual and Reset
    
*/

#include "switchExt.h"
#include "ledExt.h"
#include "pbAMR.h"

const char PB_AUTO = 2;
const char PB_MANUAL = 3;
const char PB_RESET = 4;

const char LED_AUTO = 5;
const char LED_MANUAL = 6;
const char LED_RESET = 7;

SwitchExt pbAuto(PB_AUTO);//use pin PB_AUTO for P/B
SwitchExt pbManual(PB_MANUAL);//use pin PB_MANUAL for P/B
SwitchExt pbReset(PB_RESET);//use pin PB_RESET for P/B

PbAMR pbAmr(&pbAuto, &pbManual, &pbReset);

LedExt ledAuto(LED_AUTO);
LedExt ledManual(LED_MANUAL);
LedExt ledReset(LED_RESET);
LedExt lifeLed(LED_BUILTIN);

void setup() {

    Serial.begin(9600);

    //initialization switch
    pbAuto.init();
    pbManual.init();
    pbReset.init();

    //initialization LED's
    lifeLed.init();
    ledAuto.init();
    ledManual.init();
    ledReset.init();

    //one shoot
    ledAuto.on();
    ledManual.on();
    ledReset.on();

    delay(1000);

    ledAuto.off();
    ledManual.off();
    ledReset.off();
}

void loop() {
    lifeLed.blink(250);

    ledInfo(pbAmr.getCmd(500));//debounce time in milli second
    pbAmr.info();

}

void ledInfo(char state){
    switch (state)
    {
    case STATUS_AUTO:
        ledAuto.on();
        ledManual.off();
        ledReset.off();
        break;
    
    case STATUS_MANUAL:
        ledManual.on();
        ledAuto.off();
        ledReset.off();
        break;
    
    case STATUS_MANUAL_ON:
        ledManual.blink(250);
        ledAuto.off();
        ledReset.off();
        break;
    
    case STATUS_READY:
        ledAuto.off();
        ledManual.off();
        ledReset.off();
        break;
    
    case STATUS_RESET:
        ledReset.on();
        ledAuto.off();
        ledReset.off();
        break;
    
    default:
        break;
    }
}