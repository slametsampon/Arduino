#include <Arduino.h>
#include "SequenceTimer.h"

#define   LEDLive           13 // LED live
SequenceTimer SequenceUtama("Sequence");

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDLive, OUTPUT);
  SequenceUtama.setSetingMiliSecond(1000);//dalam milli detik
  SequenceUtama.setSetingSecond(5.25);//dalam detik
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  SequenceUtama.execute();
  if (SequenceUtama.isMiliSecondEvent()){
    digitalWrite( LEDLive, digitalRead(LEDLive) ^ 1 );
  }
}
