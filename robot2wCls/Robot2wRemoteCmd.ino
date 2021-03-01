boolean isValidCommand(char cmdVal)
{
  boolean flVal = false;
  if (cmdVal == GEAR0) flVal =  true;
  else if (cmdVal == GEAR1) flVal =  true;
  else if (cmdVal == GEAR2) flVal =  true;
  else if (cmdVal == GEAR3) flVal =  true;
  else if (cmdVal == GEAR4) flVal =  true;
  else if (cmdVal == GEAR5) flVal =  true;
  else if (cmdVal == GEAR6) flVal =  true;
  else if (cmdVal == MAJU) flVal =  true;
  else if (cmdVal == MUNDUR) flVal =  true;
  else if (cmdVal == BELOK_KIRI) flVal =  true;
  else if (cmdVal == BELOK_KANAN) flVal =  true;
  else if (cmdVal == MAJU_KIRI) flVal =  true;
  else if (cmdVal == MAJU_KANAN) flVal =  true;
  else if (cmdVal == MUNDUR_KIRI) flVal =  true;
  else if (cmdVal == MUNDUR_KANAN) flVal =  true;
  else if (cmdVal == BERHENTI) flVal =  true;
  else if (cmdVal == MENU_UTAMA) flVal =  true;
  else if (cmdVal == REMOTE) flVal =  true;
  else if (cmdVal == SENAM) flVal =  true;
  else if (cmdVal == RECORD) flVal =  true;
  else if (cmdVal == TRACKING) flVal =  true;
  else if (cmdVal == AUTO_GARIS) flVal =  true;
  else if (cmdVal == AUTO_JARAK) flVal =  true;
  else if (cmdVal == STOP_TRACK) flVal =  true;
  else if (cmdVal == STOP_RECORD) flVal =  true;
  else if (cmdVal == STOP_REMOTE) flVal =  true;
  else if (cmdVal == STOP_AUTO) flVal =  true;
  return flVal;
}
class serialCmd : public command{
  public:
    serialCmd(String id);
    char getCommand();
  private:
    String  _id;    
    char  _cmd;    
};//end class

serialCmd::serialCmd(String id): _id(id){
}
char serialCmd::getCommand(){
  char serialCmd = INV_CMD;
  if (Serial.available() > 0) {
      serialCmd = Serial.read();
      Serial.print("Cmd SR : ");
      Serial.println(serialCmd);
      if (!isValidCommand(serialCmd))serialCmd = INV_CMD;
  }  
  return serialCmd;
}
        
class bluetoothCmd : public command{
  public:
    bluetoothCmd(String id);
    virtual char getCommand();
  private:
    char  _cmd;
    String  _id;    
};//end class
bluetoothCmd::bluetoothCmd(String id): _id(id){
}
char bluetoothCmd::getCommand(){
  char bluetoothCmd = INV_CMD;
  if (Serial1.available() > 0) {
      bluetoothCmd = Serial1.read();
      if (bluetoothCmd != STOP_BT){
        Serial.print("Cmd BT : ");
        Serial.println(bluetoothCmd);
        if (!isValidCommand(bluetoothCmd))bluetoothCmd = INV_CMD;
      }
  }
  return bluetoothCmd;
}

class allCommands :public command{
  public:
    allCommands(serialCmd *serVal, bluetoothCmd *btVal, LcdTft *tftVal);
    char getCommand();    
  private:
    serialCmd *SerCmd;
    bluetoothCmd *BT_Cmd;
    LcdTft *tftLCD_Cmd;
    char _prevCmd;
};
allCommands::allCommands(serialCmd *serVal, bluetoothCmd *btVal, LcdTft *tftVal):
    SerCmd(serVal),BT_Cmd(btVal), tftLCD_Cmd(tftVal){}

char allCommands::getCommand(){
  char validCmd = _prevCmd;
  char cmd;
  
  cmd = tftLCD_Cmd->getCommand();
  if (cmd != INV_CMD)validCmd = cmd;

  cmd = SerCmd->getCommand();
  if (cmd != INV_CMD)validCmd = cmd;

  cmd = BT_Cmd->getCommand();
  if (cmd != INV_CMD)validCmd = cmd;

  return validCmd;     
}
