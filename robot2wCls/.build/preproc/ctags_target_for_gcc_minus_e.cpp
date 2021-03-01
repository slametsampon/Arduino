# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"



/*

//-------For UNO

#define   PIN_BT_RX             2 //Bluetooth RX 

#define   PIN_BT_TX             3 //Bluetooth TX

#define   PIN_SPEED_MOT_KANAN   6 //Motor Speed Kanan PWM

#define   PIN_MOT_KANAN1        7 //Motor Kanan Positive

#define   PIN_MOT_KANAN2        8 //Motor Kanan Negative

#define   PIN_SPEED_MOT_KIRI    9 //Motor Speed Kiri PWM

#define   PIN_MOT_KIRI1         10 //Motor Kiri Positive

#define   PIN_MOT_KIRI2         11 //Motor Kiri Negative

*/
# 15 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
//-------For MEGA
//#define   PIN_BT_RX             2 //Bluetooth RX, Use Serial1 
//#define   PIN_BT_TX             3 //Bluetooth TX, Use Serial1
# 68 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
//----------LCD TFT
# 102 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
//-----------------
struct cmdRobot
{
  char cmd;//Command
  unsigned long miliS;//mili second
  struct cmdRobot *next;
};

struct lcdMenu
{
  char title[15];//page menu title
  byte level;//level of deepness of menu
};

struct sensorRobot
{
  int Kiri;//Sensor kiri
  int Kanan;//Sensor kanan
  int JarakKiri;//Sensor jarak kiri
  int JarakLurus;//Sensor jarak Lurus
  int JarakKanan;//Sensor jarak kiri
};

struct freeRobot
{
  boolean Kiri;//Sensor kiri
  boolean Kanan;//Sensor kanan
  boolean JarakKiri;//Sensor jarak kiri
  boolean JarakLurus;//Sensor jarak Lurus
  boolean JarakKanan;//Sensor jarak kiri
};

struct modeRobot{
  boolean Utama;
  boolean Senam;
  boolean Remote;
  boolean Record;
  boolean Tracking;
  boolean AutoGaris;
  boolean AutoJarak;
};

enum
{
  // The first register starts at address 0
//Data perintah
  PAGE_UTAMA, //index 0    
  PAGE_REMOTE, //index 1    
  PAGE_SENAM, //index 2    
  PAGE_RECORD, //index 3    
  PAGE_TRACKING, //index 4    
  PAGE_AUTO_GARIS, //index 5    
  PAGE_AUTO_JARAK, //index 6
  MAX_MODE
  // total number of registers
};
boolean printDiagOK = false;


volatile byte menuPage;
char* menuTitle[] = {"ROBOT CERDAS", "MODE REMOTE", "MODE SENAM",
                      "MODE RECORD", "MODE TRACKING", "MODE A.GARIS", "MODE A.JARAK"};

struct cmdRobot* frontCmdSenam = 
# 165 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino" 3 4
                                __null
# 165 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
                                    ;
struct cmdRobot* rearCmdSenam = 
# 166 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino" 3 4
                               __null
# 166 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
                                   ;
struct cmdRobot* frontCmdTrack = 
# 167 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino" 3 4
                                __null
# 167 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
                                    ;
struct cmdRobot* rearCmdTrack = 
# 168 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino" 3 4
                               __null
# 168 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
                                   ;
modeRobot ModeRobot;
volatile int iTrack = 0;
volatile int iSnm = 0;
volatile int iRcd = 0;
unsigned long prevRcdMs;

//this funtion is special treatment
boolean isRobotBusy(modeRobot modeVal){
  if (modeVal.Senam) return true;
  if (modeVal.Remote) return true;
  if (modeVal.Record) return true;
  if (modeVal.Tracking) return true;
  if (modeVal.AutoGaris) return true;
  if (modeVal.AutoJarak) return true;
  else return false;
}
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Asensor.ino"
# 2 "f:\\DATA\\Project\\Izan\\robot2wCls\\Asensor.ino" 2
# 3 "f:\\DATA\\Project\\Izan\\robot2wCls\\Asensor.ino" 2

class asensor{
  public:
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
    int _val;
private:
};

class sensorGaris : public asensor{
  public:
    sensorGaris(unsigned char pin);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
  private:
    unsigned char _pin;
};
sensorGaris::sensorGaris(unsigned char pin): _pin(pin){
}

void sensorGaris::init(){
  //do nothings for moment 
}

int sensorGaris::getValue(){
  _val = analogRead(_pin);
  return _val;
}

boolean sensorGaris::isFree(int minVal){
  boolean flVal = true;
  this->getValue();
  if(_val <= minVal) flVal = false;
  return flVal;
}

class sensorJarak : public asensor{
  public:
    sensorJarak(NewPing *sonarVal);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);

  private:
    NewPing *_sonar;
};
sensorJarak::sensorJarak(NewPing *sonarVal): _sonar(sonarVal){ }

void sensorJarak::init(){
  //do nothings for moment 
}

int sensorJarak::getValue(){
  _val = _sonar->ping_cm();
  return _val;
}

boolean sensorJarak::isFree(int minVal){
  boolean flVal = true;
  this->getValue();
  if(_val <= minVal) flVal = false;
  return flVal;
}

class kepala{
  public:
    kepala(sensorJarak *sensJarak, Servo *arah);
    void init(int pinServo);
    int tengokKanan();
    int tengokKiri();
    int tengokLurus();
    boolean isTengokKananFree(int minVal);
    boolean isTengokKiriFree(int minVal);
    boolean isTengokLurusFree(int minVal);

  private:
    sensorJarak *_sensJarak;
    Servo *_arah;
};
kepala::kepala(sensorJarak *sensJarak, Servo *arah): _sensJarak(sensJarak),
                                                  _arah(arah){ }

void kepala::init(int pinServo){
  _arah->attach(pinServo);
}

int kepala::tengokKanan(){
  _arah->write(180 /*Orientasi ukur jarak Kanan*/);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokKiri(){
  _arah->write(0 /*Orientasi ukur jarak Kiri*/);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokLurus(){
  _arah->write(90 /*Orientasi ukur jarak Lurus*/);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

boolean kepala::isTengokKananFree(int minVal){
  this->tengokKanan();
  return _sensJarak->isFree(minVal);
}

boolean kepala::isTengokKiriFree(int minVal){
  this->tengokKiri();
  return _sensJarak->isFree(minVal);
}

boolean kepala::isTengokLurusFree(int minVal){
  this->tengokLurus();
  return _sensJarak->isFree(minVal);
}
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Command.ino"
/*

 * It is base/master class for remote and LCD command

 */
# 4 "f:\\DATA\\Project\\Izan\\robot2wCls\\Command.ino"
class command{
  public:
    virtual char getCommand();
};
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\LcdTftClass.ino"
# 2 "f:\\DATA\\Project\\Izan\\robot2wCls\\LcdTftClass.ino" 2
# 3 "f:\\DATA\\Project\\Izan\\robot2wCls\\LcdTftClass.ino" 2
# 4 "f:\\DATA\\Project\\Izan\\robot2wCls\\LcdTftClass.ino" 2

// ALL Touch panels and wiring is DIFFERENT
// copy-paste resul_ts from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT=175,TS_RT=905,TS_TOP=932,TS_BOT=200;

class LcdTft:public command{
struct touchPixel
  {
    int x;
    int y; //Touch_getXY() updates global vars
  };

  public:
    LcdTft (String id){
      _id = id;
    }

    String getId(){
      return _id;
    }

    modeRobot getModeRobot(){
      return _modeRobot;
    }

    void setModeRobot(modeRobot modeVal){
      _modeRobot = modeVal;
    }

    void initLCD(void)
      {
        uint16_t ID = _tft.readID();
        Serial.print("TFT ID = 0x");
        Serial.println(ID, 16);
        Serial.println("Calibrate for your Touch Panel");
        if (ID == 0xD3D3) ID = 0x9486; // write-only shield
        _tft.begin(ID);
        _tft.setRotation(0); //PORTRAIT
        _tft.fillScreen(0x0000);
      }

    void initComponentsLcd(){
      _remoteBtn.initButton(&_tft, 60, 125, 110, 60, 0xFFFF, 0x07FF, 0x0000, "REMOTE", 2);
      _recordBtn.initButton(&_tft, 180, 125, 110, 60, 0xFFFF, 0x07FF, 0x0000, "RECORD", 2);
      _senamBtn.initButton(&_tft, 60, 195, 110, 60, 0xFFFF, 0x07FF, 0x0000, "SENAM", 2);
      _trackingBtn.initButton(&_tft, 180, 195, 110, 60, 0xFFFF, 0x07FF, 0x0000, "TRACKING", 2);
      _autoGarisBtn.initButton(&_tft, 60, 270, 110, 60, 0xFFFF, 0x07FF, 0x0000, "A.GARIS", 2);
      _autoJarakBtn.initButton(&_tft, 180, 270, 110, 60, 0xFFFF, 0x07FF, 0x0000, "A.JARAK", 2);
      _mainBtn.initButton(&_tft, 120, 270, 140, 60, 0xFFFF, 0x07FF, 0x0000, "MENU UTAMA", 2);
    }

    void displayLcd(int xPos, int yPos, int lebar, int tinggi,String strVal){
      _tft.fillRect(xPos,yPos,lebar,tinggi,0x0000);//0,100,240,120
      _tft.setTextColor(0xFFFF);
      _tft.setTextSize(2);
      _tft.setCursor(xPos, yPos);
      _tft.println(strVal);
    }

    void displayHeaderLCD(char titleVal[15]){
      //Header Main Menu
      _tft.fillScreen(0x0000);
      _tft.fillRoundRect(20, 20, 200, 60,20,0x001F);
      _tft.drawRoundRect(20, 20, 200, 60,20,0xFFFF);
      _tft.setTextColor(0xFFE0);
      _tft.setTextSize(2);
      _tft.setCursor(50, 40);
      _tft.print(titleVal);
      //-----------------  
    }

    byte getLcdPage(){
      return _lcdPage;
    }

    void setLcdPage(byte pageVal){
      _lcdPage = pageVal;
    }

    virtual char getCommand(){
      bool down = this->Touch_getXY();
      delay(100);
      _lcdCmd = '%' /*Stop Bluetooth Command*/;
      if (down){
        if(_modeRobot.Utama)this->getRootCmd(down);
        if(_modeRobot.Remote)this->getSubCmd(down);
        if(_modeRobot.Record)this->getSubCmd(down);
        if(_modeRobot.Senam)this->getSubCmd(down);
        if(_modeRobot.Tracking)this->getSubCmd(down);
        if(_modeRobot.AutoGaris)this->getSubCmd(down);
        if(_modeRobot.AutoJarak)this->getSubCmd(down);
        Serial.print("TFT LCD : ");
        Serial.println(_lcdCmd);
      }
      return _lcdCmd;
    }

    void displayPage(byte pageVal){
      _lcdPage = pageVal;
      switch (_lcdPage){
        case PAGE_UTAMA:
          this->displayHeaderLCD(menuTitle[_lcdPage]);
          this->initMenuUtamaLcd();
        break;
        case PAGE_REMOTE:
        case PAGE_SENAM:
        case PAGE_RECORD:
        case PAGE_TRACKING:
        case PAGE_AUTO_GARIS:
        case PAGE_AUTO_JARAK:
          this->displayHeaderLCD(menuTitle[_lcdPage]);
          _mainBtn.drawButton(false);
        break;
        default:
          //do any things
        break;
      }
    }

  private:
    touchPixel _pixel;
    modeRobot _modeRobot;
    boolean printDiagOK = false;
    byte _lcdPage;//not define yet to display header
    String _id;
    char _lcdCmd;
    Adafruit_GFX_Button _mainBtn, _remoteBtn, _senamBtn, _recordBtn,
                        _trackingBtn, _autoGarisBtn, _autoJarakBtn;
    TouchScreen _ts = TouchScreen(XP, YP, XM, YM, 300);
    MCUFRIEND_kbv _tft;

    void getRootCmd(bool lcdPress){
      _remoteBtn.press(lcdPress && _remoteBtn.contains(_pixel.x, _pixel.y));
      _senamBtn.press(lcdPress && _senamBtn.contains(_pixel.x, _pixel.y));
      _recordBtn.press(lcdPress && _recordBtn.contains(_pixel.x, _pixel.y));
      _trackingBtn.press(lcdPress && _trackingBtn.contains(_pixel.x, _pixel.y));
      _autoGarisBtn.press(lcdPress && _autoGarisBtn.contains(_pixel.x, _pixel.y));
      _autoJarakBtn.press(lcdPress && _autoJarakBtn.contains(_pixel.x, _pixel.y));
      // it jus pressed moment        
      if (_remoteBtn.justPressed()) {
        _remoteBtn.drawButton(true);
        _lcdCmd = 'L' /*Robot Remote/Linnk by Remote Control*/;
      }

      if (_senamBtn.justPressed()) {
        _senamBtn.drawButton(true);
        _lcdCmd = 'S' /*Robot Senam Mode*/;
      }
      if (_recordBtn.justPressed()) {
        _recordBtn.drawButton(true);
        _lcdCmd = 'R' /*Robot Record Action*/;
      }
      if (_trackingBtn.justPressed()) {
        _trackingBtn.drawButton(true);
        _lcdCmd = 'T' /*Play on Tracking record*/;
      }
      if (_autoGarisBtn.justPressed()) {
        _autoGarisBtn.drawButton(true);
        _lcdCmd = 'Q' /*Play on Auto garis*/;
      }
      if (_autoJarakBtn.justPressed()) {
        _autoJarakBtn.drawButton(true);
        _lcdCmd = 'J' /*Play on Auto Jarak*/;
      }
    }

    void getSubCmd(bool lcdPress){
      //if (_mainBtn.justReleased())_mainBtn.drawButton();
      _mainBtn.press(lcdPress && _mainBtn.contains(_pixel.x, _pixel.y));
      if (_mainBtn.justPressed()){
        _mainBtn.drawButton(true);
        _lcdCmd = 'M' /*Robot in Main menu */;
      }
    }
    void initMenuUtamaLcd(){
      _tft.setTextColor(0xFFFF);
      _tft.setTextSize(1);
      _tft.setCursor(150, 67);
      //_tft.setCursor(170, 290);
      _tft.print("By : Izan");

      //draw components        
      _remoteBtn.drawButton(false);
      _senamBtn.drawButton(false);
      _recordBtn.drawButton(false);
      _trackingBtn.drawButton(false);
      _autoGarisBtn.drawButton(false);
      _autoJarakBtn.drawButton(false);
    }

    bool Touch_getXY(void)
      {
        TSPoint p = _ts.getPoint();
        pinMode(YP, 0x1); //restore shared pins
        pinMode(XM, 0x1);
        digitalWrite(YP, 0x1); //because TFT control pins
        digitalWrite(XM, 0x1);
        bool pressed = (p.z > 200 && p.z < 1000);
        if (pressed) {
          _pixel.x = map(p.x, TS_LEFT, TS_RT, 0, _tft.width()); //.kbv makes sense to me
          _pixel.y = map(p.y, TS_TOP, TS_BOT, 0, _tft.height());
        }
      if (pressed){
      }
        return pressed;
      }

};// end of class
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2w.ino"
# 2 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2w.ino" 2

typedef void (*CallBackFunction) ();
class robot2W
{
  public:
    void init(){
      _normalSpeed = 0xFF /*255*/*6/6 /*Max Gear position*/;
      _turnSpeed = _normalSpeed*10 /*in percentage*//100;
      _motKiri->setSpeed(_normalSpeed);
      _motKanan->setSpeed(_normalSpeed);
      _gearPost = 6;
      _canMove = true;
      _Kepala->init(46 /*Pin Servo motor*/);
    }

    void addSensorGaris(sensorGaris *senKiri, sensorGaris *senKanan){
      _sensorGarisKiri = senKiri;
      _sensorGarisKanan = senKanan;
    }

    void addMotors(L298N *motKiri, L298N *motKanan){
      _motKiri = motKiri;
      _motKanan = motKanan;
    }

    void addHead(kepala *Kepala){
      _Kepala = Kepala;
    }

    char getCurCmd(){
      return _curCmd;
    }

    bool isMoveable(){
      return _canMove;
    }

    void reset(){
      _canMove = true;
    }

    String displayAction(){
      String strVal;
      strVal = ("Gear : ");
      strVal = (strVal + this->_gearPost);
      strVal = (strVal + "\n");
      strVal = (strVal + this->_curCmdStr);
      strVal = (strVal + "\nmilli S : ");
      strVal = (strVal + _cmdFor.miliS);
      return strVal;
    }

    void actionFor(cmdRobot cmdFor){
      this->actionFor(cmdFor,dummyCallback);
      _cmdFor.miliS = 0;
    }

    void actionFor(cmdRobot cmdFor, CallBackFunction callbackFor){
      _cmdFor = cmdFor;
      if ((_lastMs == 0) && (_canMove)){
        this->action(_cmdFor.cmd);
        _lastMs = millis();
      }
      if (((millis() - _lastMs) > _cmdFor.miliS ) && (_canMove)){
        _canMove = false;
        _lastMs = 0;

        callbackFor();
      }
    }

    void action(char incomingCmd) {
        if ((incomingCmd >= '0' /*Gear position 0*/) && (incomingCmd <= '6' /*Gear position 6*/)) this->pindahGigi(incomingCmd);
        if ((incomingCmd >= 'A' /*Robot Maju*/) && (incomingCmd <= 'I' /*Stop Bluetooth Command*/)) this->Jalan(incomingCmd);
    }

    sensorRobot getSensor(){
      _sensorRobot.Kiri = _sensorGarisKiri->getValue();
      _sensorRobot.Kanan = _sensorGarisKanan->getValue();
      _sensorRobot.JarakKanan = _Kepala->tengokKanan();
      _sensorRobot.JarakLurus = _Kepala->tengokLurus();
      _sensorRobot.JarakKiri = _Kepala->tengokKiri();

      return _sensorRobot;
    }

    freeRobot getFree(){
      _freeRobot.Kiri = _sensorGarisKiri->isFree(80 /*Batas gelap - terang*/);
      _freeRobot.Kanan = _sensorGarisKanan->isFree(80 /*Batas gelap - terang*/);
      _freeRobot.JarakKanan = _Kepala->isTengokKananFree(20 /* Maximum jarak aman cm */);
      _freeRobot.JarakLurus = _Kepala->isTengokLurusFree(20 /* Maximum jarak aman cm */);
      _freeRobot.JarakKiri = _Kepala->isTengokKiriFree(20 /* Maximum jarak aman cm */);

      return _freeRobot;
    }

  private:
    unsigned short _normalSpeed, _turnSpeed;
    char _prevMove, _gearPost, _curCmd;//previous movement command
    unsigned long _lastMs;
    unsigned long _prevSimMs;
    bool _canMove;
    String _curCmdStr;
    sensorRobot _sensorRobot;
    freeRobot _freeRobot;
    cmdRobot _cmdFor;
    L298N *_motKiri, *_motKanan;
    sensorGaris *_sensorGarisKiri, *_sensorGarisKanan;
    kepala *_Kepala;

    static void dummyCallback(){

    }
    void Jalan(char incomingCmd){
      switch (incomingCmd) {
        case 'I' /*Stop Bluetooth Command*/:
          _curCmd = incomingCmd;
          _curCmdStr = "BERHENTI";
          _motKiri->stop();
          _motKanan->stop();
          _prevMove = incomingCmd;
          break;
        case 'A' /*Robot Maju*/:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case 'F' /*Robot Maju Serong Kanan*/:
          _curCmdStr = "MAJU_KANAN";
          _curCmd = incomingCmd;
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case 'E' /*Robot Maju Serong Kiri*/:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case 'B' /*Robot Mundur*/:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case 'H' /*Robot Mundur Serong Kanan*/:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KANAN";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case 'G' /*Robot Mundur Serong Kiri*/:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case 'D' /*Robot Belok Kanan*/:
          _curCmd = incomingCmd;
          _curCmdStr = "BELOK_KANAN";
          _motKiri->forward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case 'C' /*Robot Belok Kiri*/:
          _curCmd = incomingCmd;
          _curCmdStr = "BELOK_KIRI";
          _motKiri->backward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        default:
        break;
      }
  }
  void pindahGigi(char gearVal){
    String inString = "";
    inString = (char)gearVal;
    _gearPost = inString.toInt();
    _normalSpeed = 0xFF /*255*/*_gearPost/6 /*Max Gear position*/;
    _turnSpeed = _normalSpeed*100/10 /*in percentage*/;
    this->action(_prevMove);// go to previous command
    if (_gearPost == 0)this->Jalan('I' /*Stop Bluetooth Command*/);
  }
};
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wMgr.ino"
# 2 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wMgr.ino" 2
# 3 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wMgr.ino" 2

LcdTft tftLCD("LCD Display");
Servo arahJarak;
NewPing sonar(47 /* Arduino pin tied to trigger pin on the ultrasonic sensor.*/, 48 /* Arduino pin tied to echo pin on the ultrasonic sensor.*/, 200 /* Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.*/); // NewPing setup of pins and maximum distance.
L298N motorKanan(44 /*Motor Speed Kanan PWM*/, 50 /*Motor Kanan Positive*/, 51 /*Motor Kanan Negative*/);
L298N motorKiri(45 /*Motor Speed Kiri PWM*/, 52 /*Motor Kiri Positive*/, 53 /*Motor Kiri Negative*/);
sensorGaris garisKiri(A8 /*Pin sensor cahaya kiri*/);
sensorGaris garisKanan(A9 /*Pin sensor cahaya kanan*/);
sensorJarak jarak(&sonar);
kepala Kepala(&jarak, &arahJarak);

class robotMgr{
  public:
    robotMgr(robot2W *Robot):_Robot(Robot){
      _Robot->init();
      _Robot->action('I' /*Stop Bluetooth Command*/);
    }

    void setupAcc(){
      _Robot->addMotors(&motorKiri, &motorKanan);
      _Robot->addSensorGaris(&garisKiri, &garisKanan);
      _Robot->addHead(&Kepala);
    }

    void action(char cmdVal){
      char _cmd = cmdVal;
      _Robot->action(_cmd);
    }

    void actionFor(cmdRobot *cmdVal){
      if (!this->isMoveable()){
        _cmdFor = *cmdVal;
        _Robot->reset();
      }
      else _Robot->actionFor(_cmdFor);
    }

    String displayAction(){
      return _Robot->displayAction();
    }

    char getCurCmd(){
      return _Robot->getCurCmd();
    }
    bool isMoveable(){
      return _Robot->isMoveable();
    }

    bool autoGaris(){
      char prevCmd = _Robot->getCurCmd();//previous command

      _freeRobot = _Robot->getFree();// getFree

      if(_freeRobot.Kiri && _freeRobot.Kanan){
        if ((byte) random(0, 2))_Robot->action('E' /*Robot Maju Serong Kiri*/);
        else _Robot->action('F' /*Robot Maju Serong Kanan*/);
      }
      if(!_freeRobot.Kiri && _freeRobot.Kanan)_Robot->action('C' /*Robot Belok Kiri*/);
      if(_freeRobot.Kiri && !_freeRobot.Kanan)_Robot->action('D' /*Robot Belok Kanan*/);
      if(!_freeRobot.Kiri && !_freeRobot.Kanan){
        if (!_Robot->isMoveable()){
          if ((byte) random(0, 2))_Robot->action('E' /*Robot Maju Serong Kiri*/);
          else _Robot->action('F' /*Robot Maju Serong Kanan*/);
          _Robot->reset();
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }

    bool autoJarak(){
      char prevCmd = _Robot->getCurCmd();//previous command
      _freeRobot = _Robot->getFree();// getFree

      if(_freeRobot.JarakLurus)_Robot->action('A' /*Robot Maju*/);//lurus aman dari halangan
      else{
        if (_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action('C' /*Robot Belok Kiri*/);
        if (!_freeRobot.JarakKiri && _freeRobot.JarakKanan) _Robot->action('D' /*Robot Belok Kanan*/);
        if (!_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action('B' /*Robot Mundur*/);
        else {
          if (!_Robot->isMoveable()){
            _cmdFor.miliS = 1500 /* lama gerakan random robot dalam milli detik*/;
            _cmdFor.cmd = (byte) random(0, 2);
            if ((byte) random(0, 2))_cmdFor.cmd = 'C' /*Robot Belok Kiri*/;
            else _cmdFor.cmd = 'D' /*Robot Belok Kanan*/;
            _Robot->reset();
          }
          _Robot->actionFor(_cmdFor);
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }

  private:
    String _id;
    cmdRobot _cmdFor;
    sensorRobot _sensorRobot;
    freeRobot _freeRobot;
    robot2W *_Robot;
};
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wRemoteCmd.ino"
boolean isValidCommand(char cmdVal)
{
  boolean flVal = false;
  if (cmdVal == '0' /*Gear position 0*/) flVal = true;
  else if (cmdVal == '1' /*Gear position 1*/) flVal = true;
  else if (cmdVal == '2' /*Gear position 2*/) flVal = true;
  else if (cmdVal == '3' /*Gear position 3*/) flVal = true;
  else if (cmdVal == '4' /*Gear position 4*/) flVal = true;
  else if (cmdVal == '5' /*Gear position 5*/) flVal = true;
  else if (cmdVal == '6' /*Gear position 6*/) flVal = true;
  else if (cmdVal == 'A' /*Robot Maju*/) flVal = true;
  else if (cmdVal == 'B' /*Robot Mundur*/) flVal = true;
  else if (cmdVal == 'C' /*Robot Belok Kiri*/) flVal = true;
  else if (cmdVal == 'D' /*Robot Belok Kanan*/) flVal = true;
  else if (cmdVal == 'E' /*Robot Maju Serong Kiri*/) flVal = true;
  else if (cmdVal == 'F' /*Robot Maju Serong Kanan*/) flVal = true;
  else if (cmdVal == 'G' /*Robot Mundur Serong Kiri*/) flVal = true;
  else if (cmdVal == 'H' /*Robot Mundur Serong Kanan*/) flVal = true;
  else if (cmdVal == 'I' /*Stop Bluetooth Command*/) flVal = true;
  else if (cmdVal == 'M' /*Robot in Main menu */) flVal = true;
  else if (cmdVal == 'L' /*Robot Remote/Linnk by Remote Control*/) flVal = true;
  else if (cmdVal == 'S' /*Robot Senam Mode*/) flVal = true;
  else if (cmdVal == 'R' /*Robot Record Action*/) flVal = true;
  else if (cmdVal == 'T' /*Play on Tracking record*/) flVal = true;
  else if (cmdVal == 'Q' /*Play on Auto garis*/) flVal = true;
  else if (cmdVal == 'J' /*Play on Auto Jarak*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  return flVal;
}
class serialCmd : public command{
  public:
    serialCmd(String id);
    char getCommand();
  private:
    String _id;
    char _cmd;
};//end class

serialCmd::serialCmd(String id): _id(id){
}
char serialCmd::getCommand(){
  char serialCmd = '%' /*Stop Bluetooth Command*/;
  if (Serial.available() > 0) {
      serialCmd = Serial.read();
      Serial.print("Cmd SR : ");
      Serial.println(serialCmd);
      if (!isValidCommand(serialCmd))serialCmd = '%' /*Stop Bluetooth Command*/;
  }
  return serialCmd;
}

class bluetoothCmd : public command{
  public:
    bluetoothCmd(String id);
    virtual char getCommand();
  private:
    char _cmd;
    String _id;
};//end class
bluetoothCmd::bluetoothCmd(String id): _id(id){
}
char bluetoothCmd::getCommand(){
  char bluetoothCmd = '%' /*Stop Bluetooth Command*/;
  if (Serial1.available() > 0) {
      bluetoothCmd = Serial1.read();
      if (bluetoothCmd != '%' /*Stop Bluetooth Command*/){
        Serial.print("Cmd BT : ");
        Serial.println(bluetoothCmd);
        if (!isValidCommand(bluetoothCmd))bluetoothCmd = '%' /*Stop Bluetooth Command*/;
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
  if (cmd != '%' /*Stop Bluetooth Command*/)validCmd = cmd;

  cmd = SerCmd->getCommand();
  if (cmd != '%' /*Stop Bluetooth Command*/)validCmd = cmd;

  cmd = BT_Cmd->getCommand();
  if (cmd != '%' /*Stop Bluetooth Command*/)validCmd = cmd;

  return validCmd;
}
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
robot2W robot2WD;
robotMgr RobotManager(&robot2WD);
serialCmd SerialCmd("Serial Command");
bluetoothCmd BluetoothCmd("Bluetooth Command");
allCommands AllCommands(&SerialCmd, &BluetoothCmd, &tftLCD);

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
  tempStr = String("<<<------");
  tempStr = String(tempStr + menuTitle[menuPage]);
  tempStr = String(tempStr + "------->>>"); // concatenating two strings
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
  if (cmdVal == 'M' /*Robot in Main menu */) flVal = true;
  else if (cmdVal == 'L' /*Robot Remote/Linnk by Remote Control*/) flVal = true;
  else if (cmdVal == 'S' /*Robot Senam Mode*/) flVal = true;
  else if (cmdVal == 'R' /*Robot Record Action*/) flVal = true;
  else if (cmdVal == 'T' /*Play on Tracking record*/) flVal = true;
  else if (cmdVal == 'Q' /*Play on Auto garis*/) flVal = true;
  else if (cmdVal == 'J' /*Play on Auto Jarak*/) flVal = true;
  return flVal;
}

void menuRobot(){
  char _menuCmd = AllCommands.getCommand();
  if (isMenuCommand(_menuCmd)){
    switch (_menuCmd){
      case 'M' /*Robot in Main menu */:
        RobotManager.action('I' /*Stop Bluetooth Command*/);
        ModeRobot.Utama = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_UTAMA;
        displayHeaderSerial(menuPage);
        displayMenuUtamaSerial();

        tftLCD.displayPage(menuPage);
      break;
      case 'L' /*Robot Remote/Linnk by Remote Control*/:
        ModeRobot.Utama = false;
        ModeRobot.Remote = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_REMOTE;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
      break;
      case 'S' /*Robot Senam Mode*/:
        ModeRobot.Utama = false;
        ModeRobot.Senam = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_SENAM;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iSnm = 0;
      break;
      case 'R' /*Robot Record Action*/:
        ModeRobot.Utama = false;
        ModeRobot.Record = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_RECORD;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iRcd = 0;
      break;
      case 'T' /*Play on Tracking record*/:
        ModeRobot.Utama = false;
        ModeRobot.Tracking = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_TRACKING;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
        iTrack = 0;
      break;
      case 'Q' /*Play on Auto garis*/:
        ModeRobot.Utama = false;
        ModeRobot.AutoGaris = true;
        tftLCD.setModeRobot(ModeRobot);
        menuPage = PAGE_AUTO_GARIS;
        displayHeaderSerial(menuPage);
        tftLCD.displayPage(menuPage);
      break;
      case 'J' /*Play on Auto Jarak*/:
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
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
//-----------Mode Remote
boolean isSubMenuCommand(char cmdVal){
  boolean flVal = false;
  if (cmdVal == '0' /*Gear position 0*/) flVal = true;
  else if (cmdVal == '1' /*Gear position 1*/) flVal = true;
  else if (cmdVal == '2' /*Gear position 2*/) flVal = true;
  else if (cmdVal == '3' /*Gear position 3*/) flVal = true;
  else if (cmdVal == '4' /*Gear position 4*/) flVal = true;
  else if (cmdVal == '5' /*Gear position 5*/) flVal = true;
  else if (cmdVal == '6' /*Gear position 6*/) flVal = true;
  else if (cmdVal == 'A' /*Robot Maju*/) flVal = true;
  else if (cmdVal == 'B' /*Robot Mundur*/) flVal = true;
  else if (cmdVal == 'C' /*Robot Belok Kiri*/) flVal = true;
  else if (cmdVal == 'D' /*Robot Belok Kanan*/) flVal = true;
  else if (cmdVal == 'E' /*Robot Maju Serong Kiri*/) flVal = true;
  else if (cmdVal == 'F' /*Robot Maju Serong Kanan*/) flVal = true;
  else if (cmdVal == 'G' /*Robot Mundur Serong Kiri*/) flVal = true;
  else if (cmdVal == 'H' /*Robot Mundur Serong Kanan*/) flVal = true;
  else if (cmdVal == 'I' /*Stop Bluetooth Command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  else if (cmdVal == 'X' /*Stop Track command*/) flVal = true;
  return flVal;
}
void modeRemote(){
  char chrVal;
  String strVal;
  chrVal = AllCommands.getCommand();
  if (isSubMenuCommand(chrVal)){
    if (chrVal == 'X' /*Stop Track command*/){
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
  if ((iSnm < 20 /*Max tracking record*/)&&(ptr != 
# 51 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino" 3 4
                                 __null
# 51 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
                                     )){
    if (iSnm == 0) ptr = frontCmdSenam;
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
    RobotManager.action('I' /*Stop Bluetooth Command*/);
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
# 83 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
}

//-----------Mode Record
void modeRecord(){
  char cmdRcd = AllCommands.getCommand();
  if (iRcd == 0)RobotManager.action('I' /*Stop Bluetooth Command*/);
  if (isSubMenuCommand(cmdRcd)){
    if ((cmdRcd == 'X' /*Stop Track command*/)||(iRcd >= 20 /*Max tracking record*/)){
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
   if (rearCmdTrack == 
# 108 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino" 3 4
                      __null
# 108 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
                          ) {
      rearCmdTrack = (struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdTrack->next = 
# 110 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino" 3 4
                          __null
# 110 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
                              ;
      rearCmdTrack->cmd = _cmdRcd;
      rearCmdTrack->miliS = 0;
      frontCmdTrack = rearCmdTrack;
      prevRcdMs = millis();
   } else {
      temp=(struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdTrack->next = temp;
      rearCmdTrack->cmd = _cmdRcd;
      temp->miliS = millis() - prevRcdMs;
      temp->next = 
# 120 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino" 3 4
                  __null
# 120 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
                      ;
      rearCmdTrack = temp;
   }
  Serial.println(printRecord(rearCmdTrack));
  tftLCD.displayLcd(0,100,240,120,printRecord(rearCmdTrack));
}

void autoGarisRobot(){
  String strVal;
  char cmdAuto = AllCommands.getCommand();
  if (isSubMenuCommand(cmdAuto)){
    if (cmdAuto == 'X' /*Stop Track command*/){
      strVal = ("Mode A.Garis\nSelesai");
      Serial.println("<<<----Mode A.Garis Selesai ---->>>");
      tftLCD.displayLcd(0,100,240,120,strVal);
      ModeRobot.AutoGaris = false;
      tftLCD.setModeRobot(ModeRobot);
    }
    if ((cmdAuto >= '0' /*Gear position 0*/) && (cmdAuto <= '6' /*Gear position 6*/))RobotManager.action(cmdAuto);
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
    if (cmdAuto == 'X' /*Stop Track command*/){
      strVal = ("Mode A.Jarak\nSelesai");
      Serial.println("<<<----Mode A.Jarak Selesai ---->>>");
      tftLCD.displayLcd(0,100,240,120,strVal);
      ModeRobot.AutoJarak = false;
      tftLCD.setModeRobot(ModeRobot);
    }
    if ((cmdAuto >= '0' /*Gear position 0*/) && (cmdAuto <= '6' /*Gear position 6*/))RobotManager.action(cmdAuto);
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
# 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void setup() {
  // put your setup code here, to run once:
  pinMode(13 /*LED blink*/, 0x1); // sets the digital pin as output
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial1.begin(57600 /*Baud rate Bluetooth bps*/); // opens BT serial port, sets bps
  //myBluetooth.begin(BAUD_BT);     // opens BT serial port, sets bps

  tftLCD.initLCD();
  tftLCD.initComponentsLcd();
  menuPage = PAGE_UTAMA;
  tftLCD.displayPage(menuPage);
  displayHeaderSerial(menuPage);
  displayMenuUtamaSerial();

  initPerintahSenam();

  RobotManager.setupAcc();//setup Accesories
  RobotManager.action('I' /*Stop Bluetooth Command*/);
  setModeReady();
}
void loop() {
  static unsigned long _prevMilli;
  if ((millis() - _prevMilli) >= 1000 /*Mili second*/){
    _prevMilli = millis();
    digitalWrite( 13 /*LED blink*/, digitalRead(13 /*LED blink*/) ^ 1 );
  }

  menuRobot();//Main menu for all actions (inputs and outputs for robot) 

  robotInAction();

  //watchDog();
}
void insertCmdSenam(char cmd, unsigned long milVal) {
  struct cmdRobot* temp;
   if (rearCmdSenam == 
# 36 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino" 3 4
                      __null
# 36 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
                          ) {
      rearCmdSenam = (struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdSenam->next = 
# 38 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino" 3 4
                          __null
# 38 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
                              ;
      rearCmdSenam->cmd = cmd;
      rearCmdSenam->miliS = milVal;
      frontCmdSenam = rearCmdSenam;
   } else {
      temp=(struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      rearCmdSenam->next = temp;
      temp->cmd = cmd;
      temp->miliS = milVal;
      temp->next = 
# 47 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino" 3 4
                  __null
# 47 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
                      ;
      rearCmdSenam = temp;
   }
}

void initPerintahSenam(){
  insertCmdSenam('A' /*Robot Maju*/,2000);
  insertCmdSenam('B' /*Robot Mundur*/,2000);
  insertCmdSenam('A' /*Robot Maju*/,1000);
  insertCmdSenam('D' /*Robot Belok Kanan*/,1000);
  insertCmdSenam('A' /*Robot Maju*/,1000);
  insertCmdSenam('B' /*Robot Mundur*/,2000);
  insertCmdSenam('A' /*Robot Maju*/,1000);
  insertCmdSenam('C' /*Robot Belok Kiri*/,1000);
  insertCmdSenam('A' /*Robot Maju*/,1000);
  insertCmdSenam('B' /*Robot Mundur*/,2000);
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
