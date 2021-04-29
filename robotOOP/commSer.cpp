/*
  commSer.h - Library untuk commSer
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021
  {"Test":"test Value"}
*/

#include    "commSer.h"

CommSer::CommSer(String id):_id(id){
  _dataParam = _accessParameter->getParam();
}

void CommSer::info(){
  Serial.println("CommSer::info()=>Communictaion Serial System");
  Serial.print("_id : ");
  Serial.println(_id);
  Serial.println("");
}

void CommSer::attachModelParameter(AccessParam *accessParameter){
    Serial.println("CommSer::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
  
void CommSer::attachModelCommonData(AccessCommonData *accessCommonData){
    Serial.println("CommSer::attachModelCommonData(AccessCommonData *accessCommonData)");
    _accessCommonData = accessCommonData;
  }
 
void CommSer::attachSoftwareSerial(SoftwareSerial *softSerial){
    Serial.println("CommSer::attachSoftwareSerial(SoftwareSerial *softSerial)");
    _linkSerial = softSerial;
  }
  
void CommSer::sendValue(){
  // Send the JSON document over the "link" serial port
  JsonObject valueJson = _accessParameter->getOperation();
  serializeJson(valueJson, Serial1);
  Serial1.println("");

}

void CommSer::sendParameter(){
  JsonObject paramJson = _accessParameter->getJson();
  serializeJson(paramJson, Serial1);
  Serial1.println("");

}

void CommSer::_getData(){
  /*
    ? Stream& input;

    StaticJsonDocument<192> doc;

    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    int header = doc["header"]; // 2
    const char* id = doc["id"]; // "Smoke-1"
    const char* unit = doc["unit"]; // "%"
    float value = doc["value"]; // 51.5
    int highRange = doc["highRange"]; // 100
    int lowRange = doc["lowRange"]; // 0
    int highLimit = doc["highLimit"]; // 80
    int lowLimit = doc["lowLimit"]; // 40
    float increment = doc["increment"]; // 1.1
    int alarm = doc["alarm"]; // 2
  
  */

  if (Serial1.available()) 
    {
      // Allocate the JSON document
      // This one must be bigger than for the sender because it must store the strings
      StaticJsonDocument<192> paramJson;

      // Read the JSON document from the "link" serial port
      DeserializationError err = deserializeJson(paramJson, Serial1);

      if (err == DeserializationError::Ok) 
        {
          JsonObject obj = paramJson.as<JsonObject>();

          //logic receiving data
          if(obj["id"] != _accessParameter->getId()) return;//0. Validate id
          if(obj["header"] == DATA_PARAMETER){
            _accessParameter->setParamJson(obj);//1. Remote Parameter
            _exception = REMOTE_PARAMETER_EXCEPTION;
          }
          else if (obj["header"] == DATA_OPERATION){
            _accessParameter->setOperationJson(obj);//2. Remote operation
            _exception = REMOTE_MODE_EXCEPTION;
          }
        } 
      else 
        {
          // Print error to the "debug" serial port
          Serial.print("deserializeJson() returned ");
          Serial.println(err.c_str());
      
          // Flush all bytes in the "link" serial port buffer
          while (Serial1.available() > 0)
            Serial1.read();
        }
    }
}

int CommSer::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void CommSer::execute(){
  this->_getData();
}
