#include "RelayProt.h"
#include <Arduino.h>
#define   TestSW            2 // Test Switch
#define   ResetSW           3 // Reset Switch
#define   LED_SH            5 // LED Short Circuit
#define   LED_UF            6 // LED Under Frequency
#define   LED_OF            7 // LED Over Frequency
#define   RL_Out            8 // Relay Output
RelayProt RelayShortCirt("RL_Short");
void setup() {
  // put your setup code here, to run once:
  RelayShortCirt.setPinTest(TestSW);
  RelayShortCirt.setPinReset(ResetSW);
  RelayShortCirt.setPinLED(LED_SH);
  RelayShortCirt.setPinRL(RL_Out);
  RelayShortCirt.setActive(true);
  RelayShortCirt.setSetting(255.0);//set setting value
}

void loop() {
  // put your main code here, to run repeatedly:
  RelayShortCirt.execute(200.1);//beri nilai dan jalankan 
}
