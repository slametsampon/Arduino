/*
  commSer.h - Library untuk commSer
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021

? value
StaticJsonDocument<48> doc;

doc["id"] = "Smoke-1";
doc["value"] = 51.5;

serializeJson(doc, output);

? Stream& input;

StaticJsonDocument<48> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

const char* id = doc["id"]; // "Smoke-1"
float value = doc["value"]; // 51.5

! CommSer functionality :
? 1. Send parameter as requested by EoN
? 2. Send process value if exception occur
? 3. Receive command from EoN
? 4. Receive parameter from EoN
*/

#ifndef commSer_h
#define commSer_h

#include    "Arduino.h"
#include    <SoftwareSerial.h>
#include    "src\model\model.h"
#include    "src\global\robotConstOOP.h"

class CommSer
{
  public:

    CommSer(String);//constructor
    void info();
    void sendValue();
    void sendParameter();
    void attachModelParameter(AccessParam*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachSoftwareSerial(SoftwareSerial*);//Pasang SoftwareSerial, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    int getException();
    void execute();

  private:

    String _id;
    int _exception = NO_EXCEPTION;

    AccessParam *_accessParameter;
    param _dataParam;
    SoftwareSerial *_linkSerial; // RX, TX

    void _getData();//get data incoming from serial1 and put on parameter
};//end of class

#endif