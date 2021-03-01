#include "DigitalControl.h" //Library buatan sendiri
DigitalControl DigCTest("DigitalControl Test");

void setup() {
  // put your setup code here, to run once:
    DigCTest.init();
    DigCTest.setFunction(ONE_SHOOT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("DigitalControl Out : ");
  Serial.println(DigCTest.execute(true));  
  delay(1000);
}
