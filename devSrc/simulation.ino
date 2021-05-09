#include <Arduino.h>
#include "src/global/arduinoUnoConst.h"
#include "src/ioDevices/digitalOutput.h"

DigitalOutput ledLife(LED_BUILTIN);

void setup() {
    Serial.begin(9600);
    ledLife.init(FORWARD_TYPE,"ledLife");
    ledLife.info();
}

// the loop function runs over and over again forever
void loop() {
    ledLife.blink(BLINK_NORMAL);
}
