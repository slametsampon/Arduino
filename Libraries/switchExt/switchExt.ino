/*
    It is just for testing only, for switchExt usage
    
*/

#include "switchExt.h"
#include "ledExt.h"

const char PB_GREEN = 2;
const char PB_YELLOW = 3;
const char PB_RED = 4;

const char LED_GREEN = 5;
const char LED_YELLOW = 6;
const char LED_RED = 7;

SwitchExt pbGreen(PB_GREEN);//use pin PB_GREEN for P/B
SwitchExt pbYellow(PB_YELLOW);//use pin PB_YELLOW for P/B
SwitchExt pbRed(PB_RED);//use pin PB_RED for P/B

LedExt greenLed(LED_GREEN);
LedExt yellowLed(LED_YELLOW);
LedExt redLed(LED_RED);
LedExt lifeLed(LED_BUILTIN);

void setup() {

    Serial.begin(9600);

    //initialization switch
    pbGreen.init();
    pbYellow.init();
    pbRed.init();

    //initialization LED's
    lifeLed.init();
    greenLed.init();
    yellowLed.init();
    redLed.init();

    //one shoot
    greenLed.on();
    yellowLed.on();
    redLed.on();

    delay(5000);

    greenLed.off();
    yellowLed.off();
    redLed.off();
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(250);

    if(pbGreen.isStatus(150))greenLed.blink(250);

    if(pbYellow.isStatus(150))yellowLed.blink(500);

    if(pbRed.isStatus(150))redLed.blink(1000);
}
