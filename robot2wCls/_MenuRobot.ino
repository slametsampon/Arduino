robot2W robot2WD;
robotMgr RobotManager(&robot2WD);
serialCmd SerialCmd("Serial Command");
bluetoothCmd BluetoothCmd("Bluetooth Command");
allCommands  AllCommands(&SerialCmd, &BluetoothCmd, &tftLCD);

unsigned long prevStopMs, idleTime;
void displayMenuUtamaSerial(){
  Serial.println(" ");
  Serial.println("M -> MENU_UTAMA");
  Serial.println("L -> REMOTE");
  Serial.println("S -> SENAM");
  Serial.println("R -> RECORD");
  Serial.println("T -> TRACKING");
  Serial.println("Q -> AUTO GARIS");
  Serial.println("J -> AUTO JARAK");
  Serial.println(" ");  
}
void displayHeaderSerial(byte pageVal){
  String tempStr;
  tempStr =  String("<<<------");
  tempStr = String(tempStr + menuTitle[menuPage]);
  tempStr = String(tempStr + "------->>>");   // concatenating two strings
  Serial.println(tempStr);
}
void robotInAction(){
  bool _mainBusy, _lcdBusy;
  
  if (ModeRobot.Remote)modeRemote();
  if (ModeRobot.Senam)modeSenam();
  if (ModeRobot.Record)modeRecord();
  if (ModeRobot.Tracking)modeTracking();
  if (ModeRobot.AutoGaris)autoGarisRobot();
  if (ModeRobot.AutoJarak)autoJarakRobot();

  _mainBusy = isRobotBusy(ModeRobot);
  _lcdBusy = isRobotBusy(tftLCD.getModeRobot());
  if(!_mainBusy && !_lcdBusy){
    if (menuPage != PAGE_UTAMA){
      ModeRobot.Utama = true;
      tftLCD.setModeRobot(ModeRobot);
      menuPage = PAGE_UTAMA;
      displayHeaderSerial(menuPage);
      displayMenuUtamaSerial();
      tftLCD.displayPage(menuPage);
    }
  }
  
}

boolean isMenuCommand(char cmdVal){
  boolean flVal = false;
  if (cmdVal == MENU_UTAMA) flVal =  true;
  else if (cmdVal == REMOTE) flVal =  true;
  else if (cmdVal == SENAM) flVal =  true;
  else if (cmdVal == RECORD) flVal =  true;
  else if (cmdVal == TRACKING) flVal =  true;
  else if (cmdVal == AUTO_GARIS) flVal =  true;
  else if (cmdVal == AUTO_JARAK) flVal =  true;
  return flVal;
}

void menuRobot(){
  char _menuCmd = AllCommands.getCommand();
  if (isMenuCommand(_menuCmd)){
    switch (_menuCmd){
      case MENU_UTAMA:      
        RobotManager.action(BERHENTI);      
        ModeRobot.Utama = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_UTAMA;
        displayHeaderSerial(menuPage);
        displayMenuUtamaSerial();
  
        tftLCD.displayPage(menuPage);
      break;
      case REMOTE:
        ModeRobot.Utama = false;
        ModeRobot.Remote = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_REMOTE;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);      
      break;
      case SENAM:
        ModeRobot.Utama = false;
        ModeRobot.Senam = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_SENAM;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iSnm = 0;
      break;
      case RECORD:
        ModeRobot.Utama = false;
        ModeRobot.Record = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_RECORD;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iRcd = 0;
      break;
      case TRACKING:
        ModeRobot.Utama = false;
        ModeRobot.Tracking = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_TRACKING;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iTrack = 0;
      break;
      case AUTO_GARIS:
        ModeRobot.Utama = false;
        ModeRobot.AutoGaris = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_AUTO_GARIS;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
      break;
      case AUTO_JARAK:
        ModeRobot.Utama = false;
        ModeRobot.AutoJarak = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_AUTO_JARAK;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
      break;
      default:
      //
      break;
    }   
  }  
}
