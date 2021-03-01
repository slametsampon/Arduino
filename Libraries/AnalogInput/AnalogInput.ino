/*  Program ini dirancang untuk Rele Proteksi
*   Dibuat oleh Abi  2017
*/
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define   pinSensor         A0 // pin Analog Keypad
#define   PV_HI 50 //High Range for PV
#define   PV_LO 0 //Low Range for PV
#define   RAW_HI 1023 //High Range 10 Bit ADC - Analog Input
#define   RAW_LO 0 //Low Range 10 Bit ADC - Analog Input

#include "AnalogInput.h" //Library buatan sendiri
AnalogInput SensorArus("Beban 1");
void setup() {
  // put your setup code here, to run once:
  unsigned char val;
  Serial.begin(9600);
  SensorArus.setPin(pinSensor);
  SensorArus.setUnit("A");
  SensorArus.setPV_Hi(PV_HI);
  SensorArus.setPV_Lo(PV_LO);
  SensorArus.setRaw_Hi(RAW_HI);
  SensorArus.setRaw_Lo(RAW_LO);
  SensorArus.setAlfaEma (40);//in percentage int (0 - 100), for EMA filter
  val = SensorArus.Init();
  if (val == NO_ERR)Serial.println("Init Success");
  else {
    Serial.print("Error Code : ");
    Serial.println(val,DEC);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("PV_RAW : ");
  Serial.print(SensorArus.getPV_Raw(),DEC);
  Serial.print(", PV : ");
  Serial.println(SensorArus.getPV(),DEC);  
  delay(1000);
}
