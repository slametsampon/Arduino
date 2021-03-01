#include "mobileRobot.h"
#include "dataModel.h"

void mobileRobot::init(){
  _normalSpeed = MAX_SPEED*6/MAX_GEAR;
  _turnSpeed = _normalSpeed*TURN_RATIO/100;
  _motKiri->setSpeed(_normalSpeed);
  _motKanan->setSpeed(_normalSpeed);
  _gearPost = 6;
  _prevCmd = MENU_UTAMA;
  _prevAction = BERHENTI;
  this->_cmdString = "BERHENTI";
//  this->_lcdTft->displayPage(_prevCmd);
}

void mobileRobot::attachCmdIn(command *cmdIn){
  _cmdInput[cmdInNbr] = cmdIn;
  cmdInNbr++;
}

void mobileRobot::attachSensor(AnalogInput *sens){
  this->_sensorGaris[this->sensNbr] = sens;
  this->sensNbr++;
}

void mobileRobot::attachMotor(L298N *motKiri, L298N *motKanan){
  _motKiri = motKiri;
  _motKanan = motKanan;
}
/*
void mobileRobot::attachLcd(lcdTft *lcd){
  this->_lcdTft = lcd;
}
*/
char mobileRobot::getCommand(){
  char rawCmd;
  for (int i=0; i < cmdInNbr; i++){
      rawCmd = _cmdInput[i]->getCommand();
      if (rawCmd != INV_CMD){
          _prevCmd = rawCmd;
          break;
      }
  }
  //_diagTool->show("rawCmd : ", "_prevCmd : ", rawCmd, _prevCmd);//(label1, label2, val1, val2)
  if (rawCmd == INV_CMD)rawCmd = _prevCmd;
  return rawCmd;
}

void mobileRobot::setCommand(char cmd){
  _prevCmd = cmd;
}

bool mobileRobot::isMoveable(){
  return _canMove;
}

void mobileRobot::doFor(struct cmdRobot *cmdFor){
  this->doFor(cmdFor,dummyCallback);
}

void mobileRobot::doFor(struct cmdRobot* cmd, CallBackFunction callbackFor){
  if((!_canMove) && (_prevMilli == 0)){
    _prevMilli = millis();
    Serial.print("cmd : ");
    Serial.print(cmd->cmd);
    Serial.print("->doFor : ");
    Serial.println(cmd->miliS, DEC);
    this->action(cmd->cmd);
  }
  else {
    if ((millis()-_prevMilli) > cmd->miliS){
      _prevMilli = 0;
      _canMove = true;
      Serial.println("doFor complete ");
      callbackFor();
    }
  }
}

void mobileRobot::autoGaris(){
  static unsigned long  _prevMilliRandom;//for random action
  static unsigned long  _prevMilli;//for random action
  bool isKiriFree, isKananFree;
  float minNum, maxNum;
  minNum = GELAP - 5;
  maxNum = GELAP + 5;
    
  if ((millis() - _prevMilli) >= 5000){
    _prevMilli = millis();
    
    //1. get and compare value from _sensorGaris and put to array _sensData
    for (int i=0; i < this->sensNbr; i++){
        delay(10);
        this->_sensorGaris[i]->setCalcType(PV_SIM);//Simulate data
        this->_sensorGaris[i]->setPVSim(random(minNum, maxNum));
        this->_sensData[i].value = this->_sensorGaris[i]->getPV();
        if (this->_sensData[i].value >= GELAP)this->_sensData[i].flFree = true;
        else this->_sensData[i].flFree = false;
    }

    for (int i=0; i < this->sensNbr; i++){
      Serial.print(i);
      Serial.print(" = ");
      Serial.print(this->_sensData[i].value);
      Serial.print(" -> ");
      Serial.println(this->_sensData[i].flFree);
    }
  }

  isKiriFree = _sensData[0].flFree; //take first data array
  isKananFree = _sensData[1].flFree; //take 2nd data array

  //2. build logic
  //2.1 bright is greather value, dark/black is lower
  if((isKiriFree) && (!isKananFree)){
    this->setCommand(BELOK_KANAN);
    this->action(BELOK_KANAN);
  }
  else if((isKiriFree) && (isKananFree)){
    this->setCommand(MAJU);
    this->action(MAJU);
  }
  else if((!isKiriFree) && (isKananFree)){
    this->setCommand(BELOK_KIRI);
    this->action(BELOK_KIRI);
  }
  else{
    //act for random from BELOK_KANAN/BELOK_KIRI
    if ((millis() - _prevMilliRandom) >= MILIS_RAND){
      _prevMilliRandom = millis();
      if (this->_prevCmd == BELOK_KANAN)this->_prevCmd=BELOK_KIRI;
      else this->_prevCmd=BELOK_KANAN;
    }
    this->setCommand(this->_prevCmd);
    this->action(this->_prevCmd);
  }
}

String mobileRobot::action(char rawCmd){

  //bypass if equal _prevAction
  if (rawCmd != this->_prevAction){
    this->_prevAction = rawCmd;
    switch (rawCmd){
      case MAJU:  
        this->_cmdString = "MAJU";
        this->_forward();
      break;
      case MUNDUR:
        this->_cmdString = "MUNDUR";
        this->_backward();
      break;
      case BELOK_KIRI:
        this->_cmdString = "BELOK_KIRI";
        this->_turnLeft();
      break;
      case BELOK_KANAN:
        this->_cmdString = "BELOK_KANAN";
        this->_turnRight();
      break;
      case MAJU_KIRI:
        this->_cmdString = "MAJU_KIRI";
        this->_forwardLeft();
      break;
      case MAJU_KANAN:
        this->_cmdString = "MAJU_KANAN";
        this->_forwardRight();
      break;
      case MUNDUR_KIRI:
        this->_cmdString = "MUNDUR_KIRI";
        this->_backwardLeft();
      break;
      case MUNDUR_KANAN:
        this->_cmdString = "MUNDUR_KANAN";
        this->_backwardRight();
      break;
      case BERHENTI:
        this->_cmdString = "BERHENTI";
        this->_stop();
      break;
      case RESET:
        this->_cmdString = "RESET";
        this->_reset();
      break;
      case GEAR0:
      case GEAR1:
      case GEAR2:
      case GEAR3:
      case GEAR4:
      case GEAR5:
      case GEAR6:
        this->_cmdString = "CHANGE GEAR";
        this->_changeGear(rawCmd);
      break;
      default:
        this->_cmdString = "Undefine";
        Serial.println(this->_cmdString);
      break;
    }
  }
  return this->_cmdString;
}

//private function definition
void mobileRobot::_forward(){
  Serial.println("forward");
  _motKiri->forward();
  _motKanan->forward();
}

void mobileRobot::_backward(){
  Serial.println("backward");
  _motKiri->backward();
  _motKanan->backward();
}

void mobileRobot::_stop(){
  Serial.println("stop");
  _motKiri->stop();
  _motKanan->stop();
}

void mobileRobot::_turnLeft(){
  Serial.println("turnLeft");
  _motKiri->backward();
  _motKanan->forward();
}

void mobileRobot::_turnRight(){
  Serial.println("turnRight");
  _motKiri->forward();
  _motKanan->backward();
}

void mobileRobot::_forwardLeft(){
  Serial.println("forwardLeft");
}

void mobileRobot::_forwardRight(){
  Serial.println("forwardRight");
}

void mobileRobot::_backwardLeft(){
  Serial.println("backwardLeft");
}

void mobileRobot::_backwardRight(){
  Serial.println("backwardRight");
}

void mobileRobot::_changeGear(char gearVal){
  Serial.print("changeGear : ");
  Serial.println(gearVal);
  String inString = "";
  inString = (char)gearVal;
  _gearPost = inString.toInt();
  _normalSpeed = MAX_SPEED*_gearPost/MAX_GEAR;
  _turnSpeed = _normalSpeed*100/TURN_RATIO;
  _motKiri->setSpeed(_normalSpeed);
  _motKanan->setSpeed(_normalSpeed);
}

void mobileRobot::_reset(){
  _canMove = false;
}
