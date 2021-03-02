/*
    It is just for testing only, for PbAMR usage
    
*/

#include "pbAMR.h"
#define PIN_AUTO    2//Pin Device Input Auto
#define PIN_MANUAL  3//Pin Device Input Manual
#define PIN_RESET   4//Pin Device Input Reset

SwitchExt pbAuto(PIN_AUTO);//use pin 2 for P/B Auto
SwitchExt pbManual(PIN_MANUAL);//use pin 3 for P/B Manual
SwitchExt pbReset(PIN_RESET);//use pin 4 for P/B Reset

PbAMR   amrPB(&pbAuto, &pbManual, &pbReset);
char prevCmd;
void setup() {
    Serial.begin(9600);

    pbAuto.init();
    pbManual.init();
    pbReset.init();
}

// the loop function runs over and over again forever
void loop() {
    char cmd = amrPB.getCmd(200);
    if (cmd != prevCmd){
        prevCmd = cmd;
        amrPB.info();//send to serial
    }
}
