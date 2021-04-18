/*
  controller.h - Library untuk controller
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021
  {"Test":"test Value"}
*/

#include    "controller.h"

Controller::Controller(String id):_id(id){}

void Controller::info(){
  Serial.println("Controller::info()");
  Serial.print("_id : ");
  Serial.println(_id);

  Serial.println("Attachment : ");
  _accessGymRecord->info();
}

void Controller::init(){
    this->_initGym();
}

void Controller::attachGymRecord(AccessCmdRecord *accessGymRecord){
    Serial.println("Controller::attachGymRecord(AccessCmdRecord *accessGymRecord)");
    _accessGymRecord = accessGymRecord;
}
  
void Controller::attachTrackRecord(AccessCmdRecord *accessTrackRecord){
    Serial.println("Controller::attachTrackRecord(AccessCmdRecord *accessTrackRecord)");
    _accessTrackRecord = accessTrackRecord;
}
  
int Controller::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void Controller::execute(int operationMode){

  if(_operationMode == operationMode) return;//exit
  _exception = LOCAL_OPERATION_EXCEPTION;
  _operationMode = operationMode;

  switch (_operationMode){
    case MODE_GYM:
      /* code */
      break;
    
    default:
      break;
  }
}

void Controller::_initGym(){
  _accessGymRecord->add(MOBILE_FORWARD,MAX_GEAR,2000);
  _accessGymRecord->add(MOBILE_BACKWARD,MAX_GEAR,2000);
  _accessGymRecord->add(MOBILE_FORWARD,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_TURN_RIGHT,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_FORWARD,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_BACKWARD,MAX_GEAR,2000);
  _accessGymRecord->add(MOBILE_FORWARD,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_TURN_LEFT,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_FORWARD,MAX_GEAR,1000);
  _accessGymRecord->add(MOBILE_BACKWARD,MAX_GEAR,2000);
  _accessGymRecord->add(MOBILE_AROUND_LEFT,MAX_GEAR,2000);
  _accessGymRecord->add(MOBILE_AROUND_RIGHT,MAX_GEAR,2000);
}