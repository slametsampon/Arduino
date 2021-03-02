/*
    It is just for testing only, for usage of :
    - FireSensor
    
*/

#include "fireSensor.h"

#define PIN_SENSOR  A1

FireSensor  sensorZone1(PIN_SENSOR);

void setup(){
    Serial.begin(9600);
    parameter param;
    Serial.println("FireSensor-setupParameter");

    //fire Zone1.
    param.id = "Smoke-1";
    param.unit = "%";
    param.highRange = 100;
    param.lowRange = 0;
    param.highLimit = 80;
    param.lowLimit = 40;

    sensorZone1.setParameter(&param);

    Serial.println(sensorZone1.toString());
}

void loop(){
    
}

