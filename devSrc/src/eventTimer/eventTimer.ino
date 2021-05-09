#include <Arduino.h>
#include "eventTimer.h"

#define   LEDLive           13 // LED live
EventTimer eventUtama("Event Timer");

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDLive, OUTPUT);
  eventUtama.setSetingMilliSecond(1000);//dalam milli detik
  eventUtama.setSetingSecond(5.25);//dalam detik
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  eventUtama.execute();
  if (eventUtama.isMilliSecondEvent()){
    digitalWrite( LEDLive, digitalRead(LEDLive) ^ 1 );
  }
}
