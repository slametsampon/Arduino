#include    "model.h"

//AccessDataMenu - Class
AccessDataMenu::AccessDataMenu(String id):_id(id){}

void AccessDataMenu::info(){
  Serial.println("AccessDataMenu::info()");
  Serial.print("_id : ");
  Serial.println(_id);
  Serial.print("menuNbr : ");
  Serial.println(menuNbr);
  Serial.println(" ");
}

void AccessDataMenu::add(dataMenu data){
  this->_dataMenu[menuNbr] = data;
  menuNbr++;
}

dataMenu AccessDataMenu::read(int index){
  return _dataMenu[index];
}

//AccessCmdRecord - Class
AccessCmdRecord::AccessCmdRecord(String id):_id(id){}

void AccessCmdRecord::info(){
  Serial.println("AccessCmdRecord::info()");
  Serial.print("_id : ");
  Serial.println(_id);
  Serial.print("_nbrRecord : ");
  Serial.println(_nbrRecord);
  Serial.println(" ");
}

void AccessCmdRecord::serialShowCmdRobot(cmdRobot *cmd){
  Serial.print("cmd->cmd : ");
  Serial.println(cmd->cmd);

  Serial.print("cmd->gear : ");
  Serial.println(cmd->gear);

  Serial.print("cmd->milliS : ");
  Serial.println(cmd->milliS);

  Serial.println(" ");
}

void AccessCmdRecord::add(char cmd, int gear, unsigned long milliS) {
  _nbrRecord++;
  cmdRobot* temp;
  if (_lastRecord == NULL) {
    _lastRecord = (cmdRobot *)malloc(sizeof(cmdRobot));
    _lastRecord->next = NULL;
    _lastRecord->cmd = cmd;
    _lastRecord->gear = gear;
    _lastRecord->milliS = milliS;
    _firstRecord = _lastRecord;
  }
  else{
    temp=(cmdRobot *)malloc(sizeof(cmdRobot));
    _lastRecord->next = temp;
    temp->cmd = cmd;
    temp->gear = gear;
    temp->milliS = milliS;
    temp->next = NULL;
    _lastRecord = temp;
  }
}

cmdRobot *AccessCmdRecord::getFirstRecord(){
  return _firstRecord;
}

//AccessParam - Class
AccessParam::AccessParam(String id):_id(id){}

void AccessParam::init(String id, param dtParam){
  _id = id;

  this->setParam(dtParam);
}

JsonObject AccessParam::getJson(){
  /*
  {
    "header":2,
    "id":"Smoke-1",
    "unit":"%",
    "value":51.5,
    "highRange":100.0,
    "lowRange":0.0,
    "highLimit":80.0,
    "lowLimit":40.0,
    "increment":1.1,
    "alarm":2
  }

  StaticJsonDocument<128> doc;

  doc["header"] = 2;
  doc["id"] = "Smoke-1";
  doc["unit"] = "%";
  doc["value"] = 51.5;
  doc["highRange"] = 100;
  doc["lowRange"] = 0;
  doc["highLimit"] = 80;
  doc["lowLimit"] = 40;
  doc["increment"] = 1.1;
  doc["alarm"] = 2;

  serializeJson(doc, output);  
  */

  // Get a reference to the root object
  StaticJsonDocument<128> doc;
  
  doc["header"] = DATA_PARAMETER;
  doc["id"] = _id;
  doc["unit"] = _dataParam.unit;
  doc["value"] = _dataParam.value;
  doc["highRange"] = _dataParam.highRange;
  doc["lowRange"] = _dataParam.lowRange;
  doc["highLimit"] = _dataParam.highLimit;
  doc["lowLimit"] = _dataParam.lowLimit;
  doc["alfaEma"] = _dataParam.alfaEma;
  doc["increment"] = _dataParam.increment;
  doc["alarm"] = _dataParam.alarm;
  doc["operationMode"] = _dataParam.operationMode;

  return doc.as<JsonObject>();
}

void  AccessParam::setParamJson(JsonObject paramJson){

  //_id = paramJson["id"];
  //_dataParam.unit = paramJson["unit"];

  _dataParam.value = paramJson["value"];
  _dataParam.highRange = paramJson["highRange"];
  _dataParam.lowRange = paramJson["lowRange"];
  _dataParam.highLimit = paramJson["highLimit"];
  _dataParam.lowLimit = paramJson["lowLimit"];
  _dataParam.alfaEma = paramJson["alfaEma"];
  _dataParam.increment = paramJson["increment"];
  _dataParam.alarm = paramJson["alarm"];
  _dataParam.operationMode = paramJson["operationMode"];

}

JsonObject AccessParam::getOperation(){
  /*
  {
    "header":2,
    "id":"Smoke-1",
    "unit":"%",
    "value":51.5,
    "operationMode":2,
    "alarm":2
  }

  StaticJsonDocument<96> doc;

  doc["header"] = 2;
  doc["id"] = "Smoke-1";
  doc["unit"] = "%";
  doc["value"] = 51.5;
  doc["operationMode"] = 2;
  doc["alarm"] = 2;

  serializeJson(doc, output);
  */

  StaticJsonDocument<96> doc;
  doc["header"] = DATA_OPERATION;
  doc["id"] = _id;
  doc["unit"] = _dataParam.unit;
  doc["value"] = _dataParam.value;
  doc["operationMode"] = _dataParam.operationMode;
  doc["alarm"] = _dataParam.alarm;

  return doc.as<JsonObject>();
}

void AccessParam::setOperationJson(JsonObject paramJson){

  _dataParam.operationMode=paramJson["operationMode"];

}

void AccessParam::info(){

  JsonObject paramJson = this->getJson();

  String str;
  for (JsonPair p : paramJson) {
    str = p.key().c_str();
    str = String (str + " : ");
    str = String (str + p.value().as<String>());
    Serial.println(str);
  }    
}

param AccessParam::getParam(){
  return _dataParam;
}

void AccessParam::setAlarm(int val){
  _dataParam.alarm =  val;
}

void AccessParam::setParam(param dataParam){

  _dataParam = dataParam;
}

boolean AccessParam::isChangeAble(int idParam){

  boolean isChangeAble = false;

  switch (idParam)
  {
    case PARAMETER_LOW_RANGE:
    case PARAMETER_HIGH_RANGE:
    case PARAMETER_LOW_LIMIT:
    case PARAMETER_HIGH_LIMIT:
    case PARAMETER_INCREMENT:
    case PARAMETER_ALFA_EMA:
      isChangeAble = true;
      break;
    
    default:
      break;
  }
  
  return isChangeAble;
}

void AccessParam::setParam(int idParam, float val){

  switch (idParam)
  {
    case PARAMETER_VALUE:
      _dataParam.value = val;
      break;

    case PARAMETER_LOW_RANGE:
      _dataParam.lowRange = val;
      break;
    
    case PARAMETER_HIGH_RANGE:
      _dataParam.highRange = val;
      break;
    
    case PARAMETER_LOW_LIMIT:
      _dataParam.lowLimit = val;
      break;
    
    case PARAMETER_HIGH_LIMIT:
      _dataParam.highLimit = val;
      break;
    
    case PARAMETER_OPERATION_MODE:
      _dataParam.operationMode = (int) val;
      break;
    
    case PARAMETER_ALARM:
      _dataParam.alarm = (int) val;
      break;
    
    case PARAMETER_INCREMENT:
      _dataParam.increment = val;
      break;

    case PARAMETER_ALFA_EMA:
      _dataParam.alfaEma = val;
      break;

    default:
      break;
  }
}

String AccessParam::getId(){
  return _id;
}

String AccessParam::toString(){
  String str = _id;
  String alm = "-N";

  str =  String(str + " ");
  str =  String(str + _dataParam.value);

  str =  String(str + _dataParam.unit);
/*  
  if (_dataParam.alarm == LOW_ALARM){
    alm = "-L";
  }
  if (_dataParam.alarm == HIGH_ALARM){
    alm = "-H";
  }
*/
  str =  String(str + alm);
  return str;
}

void AccessParam::setOperationMode(int operationMode){
  _operationMode = operationMode;
}

int AccessParam::getOperationMode(){
  return _operationMode;
}
