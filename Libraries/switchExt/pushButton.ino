/*
    It is just for testing only
    
*/

#include "switchExt.h"

switchExt SwitchTest(2);//use pin 2 for P/B

void setup() {
    SwitchTest.init();
}

// the loop function runs over and over again forever
void loop() {
    if(SwitchTest.isStatus(150)){
        digitalWrite(LED_BUILTIN, HIGH);
    }
}
