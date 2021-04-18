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
