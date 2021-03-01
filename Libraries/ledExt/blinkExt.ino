/*
    It is just for testing only
*/

#include "ledExt.h"
LedExt blinkTest(LED_BUILTIN);

void setup() {
    blinkTest.init();
}

// the loop function runs over and over again forever
void loop() {
    blinkTest.blink(500);//in milli second
}
