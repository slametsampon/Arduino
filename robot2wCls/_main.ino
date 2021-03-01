void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_LIVE, OUTPUT);      // sets the digital pin as output
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial1.begin(BAUD_BT);     // opens BT serial port, sets bps
  //myBluetooth.begin(BAUD_BT);     // opens BT serial port, sets bps

  tftLCD.initLCD();
  tftLCD.initComponentsLcd();
  menuPage = PAGE_UTAMA;
  tftLCD.displayPage(menuPage);
  displayHeaderSerial(menuPage);
  displayMenuUtamaSerial();

  initPerintahSenam();
  
  RobotManager.setupAcc();//setup Accesories
  RobotManager.action(BERHENTI);
  setModeReady();
}
void loop() {
  static unsigned long  _prevMilli;
  if ((millis() - _prevMilli) >= BLINK_TIME){
    _prevMilli = millis();
    digitalWrite( PIN_LED_LIVE, digitalRead(PIN_LED_LIVE) ^ 1 );
  }
  
  menuRobot();//Main menu for all actions (inputs and outputs for robot) 

  robotInAction();

  //watchDog();
}
void insertCmdSenam(char cmd, unsigned long milVal) {
  struct cmdRobot* temp;
   if (rearCmdSenam == NULL) {
      rearCmdSenam = (struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdSenam->next = NULL;
      rearCmdSenam->cmd = cmd;
      rearCmdSenam->miliS = milVal;
      frontCmdSenam = rearCmdSenam;
   } else {
      temp=(struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdSenam->next = temp;
      temp->cmd = cmd;
      temp->miliS = milVal;
      temp->next = NULL;
      rearCmdSenam = temp;
   }
}

void initPerintahSenam(){
  insertCmdSenam(MAJU,2000);
  insertCmdSenam(MUNDUR,2000);
  insertCmdSenam(MAJU,1000);
  insertCmdSenam(BELOK_KANAN,1000);
  insertCmdSenam(MAJU,1000);
  insertCmdSenam(MUNDUR,2000);
  insertCmdSenam(MAJU,1000);
  insertCmdSenam(BELOK_KIRI,1000);
  insertCmdSenam(MAJU,1000);
  insertCmdSenam(MUNDUR,2000);
}

void setModeReady(){
  ModeRobot.Senam = false;
  ModeRobot.Remote = false;
  ModeRobot.Record = false;
  ModeRobot.Tracking = false;
  ModeRobot.AutoGaris = false;
  ModeRobot.Utama = true;
  
  tftLCD.setModeRobot(ModeRobot);
}
