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
  _mobileRobot->info();
  _accessGymRecord->info();
}

void Controller::init(){
    _mobileRobot->init("_mobileRobot");
    this->_initGym();
    _prevCmd = _accessGymRecord->getFirstRecord();
}

void Controller::attachMobileRobot(MobileRobot *mobileRobot){
    Serial.println("Controller::attachMobileRobot(MobileRobot *mobileRobot)");
    _mobileRobot = mobileRobot;
}
  
void Controller::attachGymRecord(AccessCmdRecord *accessGymRecord){
    Serial.println("Controller::attachGymRecord(AccessCmdRecord *accessGymRecord)");
    _accessGymRecord = accessGymRecord;
}
  
void Controller::attachTrackRecord(AccessCmdRecord *accessTrackRecord){
    Serial.println("Controller::attachTrackRecord(AccessCmdRecord *accessTrackRecord)");
    _accessTrackRecord = accessTrackRecord;
}
  
void Controller::attachModelParameter(AccessParam *accessParameter){
    Serial.println("Controller::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 
void Controller::updateParameter(){
  _dataParam = _accessParameter->getParam();

}

int Controller::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void Controller::execute(int operationMode){

  if(_operationMode != operationMode){
  _exception = LOCAL_MODE_EXCEPTION;
  _operationMode = operationMode;
  }
  switch (_operationMode){
    case MODE_GYM:
      _operationModeStr = "MODE_GYM";
      this->_modeGym();
      break;
    
    default:
      break;
  }
}

String Controller::getOperationMode(){
  return _operationModeStr;
}

void Controller::serialShowOperationMode(){
  Serial.print("_operationModeStr : ");
  Serial.println(_operationModeStr);
  
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

void Controller::_modeGym(){
  if (_prevCmd != NULL){
    if (!_mobileRobot->isMoveable()){
      Serial.print("_gymStep : ");
      Serial.println(_gymStep);
      _accessGymRecord->serialShowCmdRobot(_prevCmd);
      _gymStep++;
      _prevCmd = _prevCmd->next;
      _mobileRobot->reset();
    }
    _mobileRobot->move(_prevCmd->cmd, _prevCmd->gear, _prevCmd->milliS); 
  }
  else {
    _prevCmd = _accessGymRecord->getFirstRecord();
    _gymStep = 0;
    Serial.println("<<<------Gym Completed------->>>");
  }
}

