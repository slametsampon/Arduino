#define   OUT_PIN 13 //Digital Output Pin

#include "DigitalOutput.h" //Library buatan sendiri
DigitalOutput ledLive(OUT_PIN);

void setup(void) {
  // put your setup code here, to run once:
    ledLive.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  ledLive.blink(1000);//will blink in ms, repeatedly
}
