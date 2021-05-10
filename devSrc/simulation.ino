#include <Arduino.h>
#include "src/global/arduinoUnoConst.h"
#include "src/ioDevices/digitalOutput.h"
#include "src/ioDevices/digitalInput.h"
#include "src/eventTimer/eventTimer.h"

DigitalOutput ledLife(LED_BUILTIN);

DigitalOutput ledExt(12);
DigitalInput switchExt(11);
EventTimer eventTimer("eventTimer");

void setup() {
    Serial.begin(9600);
    ledLife.init(FORWARD_TYPE,"ledLife");
    ledLife.info();

    eventTimer.setDelay(5555);
    eventTimer.setDuration(2555);
    eventTimer.attachInput(&switchExt);
    eventTimer.attachOutput(&ledExt);
    eventTimer.init(REVERSE_TYPE);
    eventTimer.setOneShoot(true);
    eventTimer.info();
}

// the loop function runs over and over again forever
void loop() {
    ledLife.blink(BLINK_NORMAL);
    if (eventTimer.execute())Serial.println("eventTimer=>OneShoot");
}
