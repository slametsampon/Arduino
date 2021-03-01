#include "signalGenerator.h"

signalGenerator randomSignal(RANDOM_TYPE);
signalGenerator sinyalSawTooth(SAWTOOTH_TYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSignal.setMinValue(250);
  randomSignal.setMaxValue(255);
  //sinyal Saw Tooth
  sinyalSawTooth.setMinValue(-100);
  sinyalSawTooth.setMaxValue(100);
  sinyalSawTooth.setPeriodTime(10000);//10 detik
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long periodTime,prevMilli,currMilli,cycleEnd;
  prevMilli = millis();
  cycleEnd = prevMilli + 1.5*sinyalSawTooth.getPeriodTime();
  Serial.print("Start Time:");
  Serial.print(prevMilli);
  Serial.print(", PeriodeTime:");
  Serial.println(sinyalSawTooth.getPeriodTime());
  while(currMilli <= cycleEnd){

    if (randomSignal.isFlRun()){
      Serial.print("Saw->");
      Serial.print(randomSignal.execute());
    }
    if (sinyalSawTooth.isFlRun()){
      Serial.print("Saw->");
      Serial.println(sinyalSawTooth.execute());
    }
    currMilli=millis();
  }
  Serial.print("End Time:");
  Serial.println(currMilli);
delay(60000);//satu menit
}
