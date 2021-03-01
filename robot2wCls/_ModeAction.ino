//-----------Mode Remote
boolean isSubMenuCommand(char cmdVal){
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
  else if (cmdVal == STOP_TRACK) flVal =  true;
  else if (cmdVal == STOP_RECORD) flVal =  true;
  else if (cmdVal == STOP_REMOTE) flVal =  true;
  else if (cmdVal == STOP_AUTO) flVal =  true;
  return flVal;
}
void modeRemote(){
  char chrVal;
  String strVal;
  chrVal = AllCommands.getCommand();
  if (isSubMenuCommand(chrVal)){
    if (chrVal == STOP_REMOTE){
      strVal = ("Mode Remote\nSelesai");
      Serial.println("<<<----Mode Remote Selesai ---->>>");      
      tftLCD.displayLcd(0,100,240,120,strVal);
      ModeRobot.Remote = false;      
      tftLCD.setModeRobot(ModeRobot);
    }  
    else {
      RobotManager.action(chrVal);
      strVal = RobotManager.displayAction();
      Serial.println(strVal);      
      tftLCD.displayLcd(0,100,240,120,strVal);
    }
  }
}

//-----------Mode Senam
void modeSenam(){
  String strVal;
  struct cmdRobot* ptr;
  if ((iSnm < MAX_TRACK)&&(ptr != NULL)){
    if (iSnm == 0)  ptr = frontCmdSenam;
    if (!RobotManager.isMoveable()){
      strVal = RobotManager.displayAction();
      tftLCD.displayLcd(0,100,240,120,strVal);
      Serial.println(strVal);
      ptr = ptr->next;
      iSnm++; 
    }
    RobotManager.actionFor(ptr); 
  }
  else {
    Serial.println("<<<------Senam selesai------->>>");
    ModeRobot.Senam = false;
    tftLCD.setModeRobot(ModeRobot);
    RobotManager.action(BERHENTI);      
    tftLCD.displayLcd(0,100,240,120,"Mode Senam\nSelesai");
  }
}

//-----------Mode Tracking
void modeTracking(){
/*  if ((iTrack < MAX_TRACK)&&(trackCmd[iTrack].cmd != INV_CMD)){
    //RobotManager.actionFor(trackCmd[iTrack]);
    if (!RobotManager.isMoveable())iTrack++;
  }
  else {
    Serial.println("<<<------Tracking selesai------->>>");
    ModeRobot.Tracking = false;
    RobotManager.action(BERHENTI);      
  }      
  */
}

//-----------Mode Record
void modeRecord(){
  char cmdRcd = AllCommands.getCommand();
  if (iRcd == 0)RobotManager.action(BERHENTI);  
  if (isSubMenuCommand(cmdRcd)){
    if ((cmdRcd == STOP_RECORD)||(iRcd >= MAX_TRACK)){
      Serial.println("<<<------RECORD selesai------->>>");
      ModeRobot.Record = false;
      //Serial.print("iRcd : ");
      //Serial.println(iRcd);
      //for (int i = 0; i<iRcd; i++){
         //Serial.println(printRecord(i));
      //}
    }  
    else {
      RobotManager.action(cmdRcd);
      updateRecord();
    }
  }
}
void updateRecord(){
  char _cmdRcd = RobotManager.getCurCmd();
  struct cmdRobot* temp;
   if (rearCmdTrack == NULL) {
      rearCmdTrack = (struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdTrack->next = NULL;
      rearCmdTrack->cmd = _cmdRcd;
      rearCmdTrack->miliS = 0;
      frontCmdTrack = rearCmdTrack;
      prevRcdMs = millis();
   } else {
      temp=(struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdTrack->next = temp;
      rearCmdTrack->cmd = _cmdRcd;
      temp->miliS = millis() - prevRcdMs;
      temp->next = NULL;
      rearCmdTrack = temp;
   }
  Serial.println(printRecord(rearCmdTrack));
  tftLCD.displayLcd(0,100,240,120,printRecord(rearCmdTrack));
}

void autoGarisRobot(){
  String strVal;
  char cmdAuto = AllCommands.getCommand();
  if (isSubMenuCommand(cmdAuto)){
    if (cmdAuto == STOP_AUTO){
      strVal = ("Mode A.Garis\nSelesai");
      Serial.println("<<<----Mode A.Garis Selesai ---->>>");      
      tftLCD.displayLcd(0,100,240,120,strVal);
      ModeRobot.AutoGaris = false;      
      tftLCD.setModeRobot(ModeRobot);
    }  
    if ((cmdAuto >= GEAR0) && (cmdAuto <= GEAR6))RobotManager.action(cmdAuto);
    else{
      if (RobotManager.autoGaris()){
        strVal = RobotManager.displayAction();
        Serial.println(strVal);      
        tftLCD.displayLcd(0,100,240,120,strVal);
      }
    }
  }
}

void autoJarakRobot(){
  String strVal;
  char cmdAuto = AllCommands.getCommand();
  if (isSubMenuCommand(cmdAuto)){
    if (cmdAuto == STOP_AUTO){
      strVal = ("Mode A.Jarak\nSelesai");
      Serial.println("<<<----Mode A.Jarak Selesai ---->>>");      
      tftLCD.displayLcd(0,100,240,120,strVal);
      ModeRobot.AutoJarak = false;      
      tftLCD.setModeRobot(ModeRobot);
    }  
    if ((cmdAuto >= GEAR0) && (cmdAuto <= GEAR6))RobotManager.action(cmdAuto);
    else{
      if (RobotManager.autoJarak()){
        strVal = RobotManager.displayAction();
        Serial.println(strVal);      
        tftLCD.displayLcd(0,100,240,120,strVal);
      }
    }
  }
}

String printRecord(struct cmdRobot* cmdVal){
  String strVal;
  strVal = ("cmd : ");
  strVal = (strVal + cmdVal->cmd);
  strVal = (strVal + "\nmiliS : ");
  strVal = (strVal + cmdVal->miliS);
  return strVal;
}
