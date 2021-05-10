#include "Comparator.h" //Library buatan sendiri
Comparator compTest("Comparator Test");

void setup() {
  // put your setup code here, to run once:
    compTest.init();
    compTest.setHigh(75.5);
    compTest.setLow(15.5);
    compTest.setFunction(LESS_THAN);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Comparator Out : ");
  Serial.println(compTest.execute(81.2));  
  delay(1000);
}
