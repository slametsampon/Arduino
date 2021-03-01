#define   DIG_PIN 9 //Digital Input Pin

#include "DigitalInput.h" //Library buatan sendiri
DigitalInput inputSwitch(DIG_PIN);

void setup(void) {
  // put your setup code here, to run once:
    inputSwitch.init();
    inputSwitch.setSimulate(false);
}

void loop() {
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. 
  // HARDWARE WIRING SHOULD BE CONCERNED !!!!! 
  Serial.print("HIGH -> open, and LOW -> pressed : ");
  Serial.println(inputSwitch.getPV());  
  delay(1000);
}
