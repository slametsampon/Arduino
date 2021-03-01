#include <Arduino.h>
#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"

#define   PIN_LED_LIVE          13 //LED blink
#define   BLINK_TIME            1000 //Mili second
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
//-------For MEGA
//#define   PIN_BT_RX             2 //Bluetooth RX, Use Serial1 
//#define   PIN_BT_TX             3 //Bluetooth TX, Use Serial1
#define   PIN_SPEED_MOT_KANAN   44 //Motor Speed Kanan PWM
#define   PIN_MOT_KANAN1        50 //Motor Kanan Positive
#define   PIN_MOT_KANAN2        51 //Motor Kanan Negative
#define   PIN_SPEED_MOT_KIRI    45 //Motor Speed Kiri PWM
#define   PIN_MOT_KIRI1         52 //Motor Kiri Positive
#define   PIN_MOT_KIRI2         53 //Motor Kiri Negative
#define   PIN_SENSOR_GARIS_KIRI     A8 //Pin sensor cahaya kiri
#define   PIN_SENSOR_GARIS_KANAN    A9 //Pin sensor cahaya kanan
#define   PIN_SENSOR_JARAK          A10 //Pin sensor cahaya kanan
#define   PIN_SERVO                 46 //Pin Servo motor

#define   TURN_RATIO            10 //in percentage
#define   MAX_SPEED             0xFF //255
#define   MAX_GEAR              6 //Max Gear position
#define   MAX_TRACK             20 //Max tracking record
#define   MAX_IDL               25000 //Max Idle time milli second

#define   STOP_BT           '%' //Stop Bluetooth Command
#define   INV_CMD           '%' //Stop Bluetooth Command
#define   STOP_TRACK        'X' //Stop Track command
#define   STOP_RECORD       'X' //Stop Track command
#define   STOP_REMOTE       'X' //Stop Track command
#define   STOP_AUTO         'X' //Stop Track command
#define   BAUD_BT           57600 //Baud rate Bluetooth bps

#define   MAJU              'A' //Robot Maju
#define   MUNDUR            'B' //Robot Mundur
#define   BELOK_KIRI        'C' //Robot Belok Kiri
#define   BELOK_KANAN       'D' //Robot Belok Kanan
#define   MAJU_KIRI         'E' //Robot Maju Serong Kiri
#define   MAJU_KANAN        'F' //Robot Maju Serong Kanan
#define   MUNDUR_KIRI       'G' //Robot Mundur Serong Kiri
#define   MUNDUR_KANAN      'H' //Robot Mundur Serong Kanan
#define   BERHENTI          'I' //Stop Bluetooth Command

#define   MENU_UTAMA        'M' //Robot in Main menu 
#define   REMOTE            'L' //Robot Remote/Linnk by Remote Control
#define   SENAM             'S' //Robot Senam Mode
#define   RECORD            'R' //Robot Record Action
#define   TRACKING          'T' //Play on Tracking record
#define   AUTO_GARIS        'Q' //Play on Auto garis
#define   AUTO_JARAK        'J' //Play on Auto Jarak
#define   GEAR0             '0' //Gear position 0
#define   GEAR1             '1' //Gear position 1
#define   GEAR2             '2' //Gear position 2
#define   GEAR3             '3' //Gear position 3
#define   GEAR4             '4' //Gear position 4
#define   GEAR5             '5' //Gear position 5
#define   GEAR6             '6' //Gear position 6

//----------LCD TFT
#define   MINPRESSURE   200
#define   MAXPRESSURE   1000

#define   BLACK         0x0000
#define   NAVY          0x000F
#define   DARKGREEN     0x03E0
#define   DARKCYAN      0x03EF
#define   MAROON        0x7800
#define   PURPLE        0x780F
#define   OLIVE         0x7BE0
#define   LIGHTGREY     0xC618
#define   DARKGREY      0x7BEF
#define   BLUE          0x001F
#define   GREEN         0x07E0
#define   CYAN          0x07FF
#define   RED           0xF800
#define   MAGENTA       0xF81F
#define   YELLOW        0xFFE0
#define   WHITE         0xFFFF
#define   ORANGE        0xFD20
#define   GREENYELLOW   0xAFE5
#define   PINK          0xF81F

#define   MAX_CAHAYA    100 //Maximum nilai cahaya
#define   GELAP         80 //Batas gelap - terang
#define   ORT_KIRI      0 //Orientasi ukur jarak Kiri
#define   ORT_KANAN     180 //Orientasi ukur jarak Kanan
#define   ORT_LURUS     90 //Orientasi ukur jarak Lurus
#define   TRIGGER_PIN   47  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define   ECHO_PIN      48  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define   MAX_DISTANCE  200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define   JARAK_AMAN    20 // Maximum jarak aman cm 
#define   MILIS_RAND    1500 // lama gerakan random robot dalam milli detik
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

struct cmdRobot* frontCmdSenam = NULL;
struct cmdRobot* rearCmdSenam = NULL;
struct cmdRobot* frontCmdTrack = NULL;
struct cmdRobot* rearCmdTrack = NULL;
modeRobot ModeRobot;
volatile int iTrack = 0;
volatile int iSnm = 0;
volatile int iRcd = 0;
unsigned long prevRcdMs;

//this funtion is special treatment
#line 176 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
boolean isRobotBusy(modeRobot modeVal);
#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wRemoteCmd.ino"
boolean isValidCommand(char cmdVal);
#line 8 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
void displayMenuUtamaSerial();
#line 19 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
void displayHeaderSerial(byte pageVal);
#line 26 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
void robotInAction();
#line 51 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
boolean isMenuCommand(char cmdVal);
#line 63 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
void menuRobot();
#line 2 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
boolean isSubMenuCommand(char cmdVal);
#line 26 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void modeRemote();
#line 48 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void modeSenam();
#line 72 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void modeTracking();
#line 86 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void modeRecord();
#line 105 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void updateRecord();
#line 127 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void autoGarisRobot();
#line 149 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
void autoJarakRobot();
#line 171 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
String printRecord(struct cmdRobot* cmdVal);
#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void setup();
#line 21 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void loop();
#line 34 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void insertCmdSenam(char cmd, unsigned long milVal);
#line 52 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void initPerintahSenam();
#line 65 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
void setModeReady();
#line 176 "f:\\DATA\\Project\\Izan\\robot2wCls\\robot2wCls.ino"
boolean isRobotBusy(modeRobot modeVal){
  if (modeVal.Senam) return true;
  if (modeVal.Remote) return true;
  if (modeVal.Record) return true;
  if (modeVal.Tracking) return true;
  if (modeVal.AutoGaris) return true;
  if (modeVal.AutoJarak) return true;
  else return false;
}

                      

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Asensor.ino"
#include <NewPing.h>
#include <Servo.h>

class asensor{
  public:    
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
    int  _val;
private:
};

class sensorGaris : public asensor{
  public:
    sensorGaris(unsigned char pin);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
  private:
    unsigned char  _pin;    
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
  if(_val <=  minVal) flVal = false;
  return flVal;
}

class sensorJarak : public asensor{
  public:
    sensorJarak(NewPing *sonarVal);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);

  private:
    NewPing  *_sonar;    
};
sensorJarak::sensorJarak(NewPing *sonarVal): _sonar(sonarVal){  }

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
  if(_val <=  minVal) flVal = false;
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
    sensorJarak  *_sensJarak;    
    Servo *_arah;
};
kepala::kepala(sensorJarak *sensJarak, Servo *arah): _sensJarak(sensJarak),
                                                  _arah(arah){  }

void kepala::init(int pinServo){
  _arah->attach(pinServo);
}

int kepala::tengokKanan(){
  _arah->write(ORT_KANAN);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokKiri(){
  _arah->write(ORT_KIRI);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokLurus(){
  _arah->write(ORT_LURUS);
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

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Command.ino"
/*
 * It is base/master class for remote and LCD command
 */
class command{
  public:    
    virtual char getCommand();
};
  

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\LcdTftClass.ino"
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

// ALL Touch panels and wiring is DIFFERENT
// copy-paste resul_ts from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT=175,TS_RT=905,TS_TOP=932,TS_BOT=200;

class LcdTft:public command{
struct touchPixel
  {
    int x;
    int y;     //Touch_getXY() updates global vars
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
        Serial.println(ID, HEX);
        Serial.println("Calibrate for your Touch Panel");
        if (ID == 0xD3D3) ID = 0x9486; // write-only shield
        _tft.begin(ID);
        _tft.setRotation(0);            //PORTRAIT
        _tft.fillScreen(BLACK);
      }

    void initComponentsLcd(){
      _remoteBtn.initButton(&_tft,  60, 125, 110, 60, WHITE, CYAN, BLACK, "REMOTE", 2);
      _recordBtn.initButton(&_tft,  180, 125, 110, 60, WHITE, CYAN, BLACK, "RECORD", 2);
      _senamBtn.initButton(&_tft,  60, 195, 110, 60, WHITE, CYAN, BLACK, "SENAM", 2);
      _trackingBtn.initButton(&_tft,  180, 195, 110, 60, WHITE, CYAN, BLACK, "TRACKING", 2);
      _autoGarisBtn.initButton(&_tft,  60, 270, 110, 60, WHITE, CYAN, BLACK, "A.GARIS", 2);
      _autoJarakBtn.initButton(&_tft,  180, 270, 110, 60, WHITE, CYAN, BLACK, "A.JARAK", 2);
      _mainBtn.initButton(&_tft,  120, 270, 140, 60, WHITE, CYAN, BLACK, "MENU UTAMA", 2);      
    }
    
    void displayLcd(int xPos, int yPos, int lebar, int tinggi,String strVal){
      _tft.fillRect(xPos,yPos,lebar,tinggi,BLACK);//0,100,240,120
      _tft.setTextColor(WHITE);
      _tft.setTextSize(2);
      _tft.setCursor(xPos, yPos);
      _tft.println(strVal);  
    }

    void displayHeaderLCD(char titleVal[15]){  
      //Header Main Menu
      _tft.fillScreen(BLACK);
      _tft.fillRoundRect(20, 20, 200, 60,20,BLUE);
      _tft.drawRoundRect(20, 20, 200, 60,20,WHITE);
      _tft.setTextColor(YELLOW);
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
      _lcdCmd = INV_CMD;
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
    touchPixel  _pixel;
    modeRobot _modeRobot;
    boolean printDiagOK = false;      
    byte _lcdPage;//not define yet to display header
    String  _id;
    char  _lcdCmd;
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
        _lcdCmd = REMOTE;
      }

      if (_senamBtn.justPressed()) {
        _senamBtn.drawButton(true);
        _lcdCmd = SENAM;
      }
      if (_recordBtn.justPressed()) {
        _recordBtn.drawButton(true);
        _lcdCmd = RECORD;
      }
      if (_trackingBtn.justPressed()) {
        _trackingBtn.drawButton(true);
        _lcdCmd = TRACKING;
      }
      if (_autoGarisBtn.justPressed()) {
        _autoGarisBtn.drawButton(true);
        _lcdCmd = AUTO_GARIS;
      }      
      if (_autoJarakBtn.justPressed()) {
        _autoJarakBtn.drawButton(true);
        _lcdCmd = AUTO_JARAK;
      }      
    }
    
    void getSubCmd(bool lcdPress){
      //if (_mainBtn.justReleased())_mainBtn.drawButton();
      _mainBtn.press(lcdPress && _mainBtn.contains(_pixel.x, _pixel.y));
      if (_mainBtn.justPressed()){
        _mainBtn.drawButton(true);                
        _lcdCmd = MENU_UTAMA;
      }
    }
    void initMenuUtamaLcd(){      
      _tft.setTextColor(WHITE);
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
        pinMode(YP, OUTPUT);      //restore shared pins
        pinMode(XM, OUTPUT);
        digitalWrite(YP, HIGH);   //because TFT control pins
        digitalWrite(XM, HIGH);
        bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
        if (pressed) {
          _pixel.x = map(p.x, TS_LEFT, TS_RT, 0, _tft.width()); //.kbv makes sense to me
          _pixel.y = map(p.y, TS_TOP, TS_BOT, 0, _tft.height());
        }
      if (pressed){
      }
        return pressed;
      }

};// end of class

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2w.ino"
#include <L298N.h>

typedef void (*CallBackFunction) ();
class robot2W
{
  public:
    void init(){
      _normalSpeed = MAX_SPEED*6/MAX_GEAR;
      _turnSpeed = _normalSpeed*TURN_RATIO/100;
      _motKiri->setSpeed(_normalSpeed);
      _motKanan->setSpeed(_normalSpeed);
      _gearPost = 6;
      _canMove = true;
      _Kepala->init(PIN_SERVO);
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
      if ((_lastMs == 0)  && (_canMove)){
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
        if ((incomingCmd >= GEAR0) && (incomingCmd <= GEAR6)) this->pindahGigi(incomingCmd);
        if ((incomingCmd >= MAJU) && (incomingCmd <= BERHENTI)) this->Jalan(incomingCmd);
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
      _freeRobot.Kiri = _sensorGarisKiri->isFree(GELAP);
      _freeRobot.Kanan = _sensorGarisKanan->isFree(GELAP);
      _freeRobot.JarakKanan = _Kepala->isTengokKananFree(JARAK_AMAN);
      _freeRobot.JarakLurus = _Kepala->isTengokLurusFree(JARAK_AMAN);
      _freeRobot.JarakKiri = _Kepala->isTengokKiriFree(JARAK_AMAN);

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
        case BERHENTI:
          _curCmd = incomingCmd;
          _curCmdStr = "BERHENTI";
          _motKiri->stop();
          _motKanan->stop();
          _prevMove = incomingCmd;
          break;
        case MAJU:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MAJU_KANAN:
          _curCmdStr = "MAJU_KANAN";
          _curCmd = incomingCmd;
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MAJU_KIRI:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR_KANAN:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KANAN";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR_KIRI:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case BELOK_KANAN:
          _curCmd = incomingCmd;
          _curCmdStr = "BELOK_KANAN";
          _motKiri->forward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case BELOK_KIRI:
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
    _normalSpeed = MAX_SPEED*_gearPost/MAX_GEAR;
    _turnSpeed = _normalSpeed*100/TURN_RATIO;
    this->action(_prevMove);// go to previous command
    if (_gearPost == 0)this->Jalan(BERHENTI); 
  }
};

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wMgr.ino"
#include <NewPing.h>
#include <Servo.h>

LcdTft tftLCD("LCD Display");
Servo arahJarak;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
L298N motorKanan(PIN_SPEED_MOT_KANAN, PIN_MOT_KANAN1, PIN_MOT_KANAN2);
L298N motorKiri(PIN_SPEED_MOT_KIRI, PIN_MOT_KIRI1, PIN_MOT_KIRI2);
sensorGaris garisKiri(PIN_SENSOR_GARIS_KIRI); 
sensorGaris garisKanan(PIN_SENSOR_GARIS_KANAN); 
sensorJarak jarak(&sonar);
kepala Kepala(&jarak, &arahJarak);

class robotMgr{
  public:
    robotMgr(robot2W *Robot):_Robot(Robot){
      _Robot->init();
      _Robot->action(BERHENTI);
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
        if ((byte) random(0, 2))_Robot->action(MAJU_KIRI);
        else _Robot->action(MAJU_KANAN);
      }
      if(!_freeRobot.Kiri && _freeRobot.Kanan)_Robot->action(BELOK_KIRI);
      if(_freeRobot.Kiri && !_freeRobot.Kanan)_Robot->action(BELOK_KANAN);
      if(!_freeRobot.Kiri && !_freeRobot.Kanan){
        if (!_Robot->isMoveable()){
          if ((byte) random(0, 2))_Robot->action(MAJU_KIRI);
          else _Robot->action(MAJU_KANAN);
          _Robot->reset();         
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }    
  
    bool autoJarak(){
      char prevCmd = _Robot->getCurCmd();//previous command
      _freeRobot = _Robot->getFree();// getFree
  
      if(_freeRobot.JarakLurus)_Robot->action(MAJU);//lurus aman dari halangan
      else{
        if (_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action(BELOK_KIRI);   
        if (!_freeRobot.JarakKiri && _freeRobot.JarakKanan) _Robot->action(BELOK_KANAN);   
        if (!_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action(MUNDUR);   
        else {
          if (!_Robot->isMoveable()){
            _cmdFor.miliS = MILIS_RAND; 
            _cmdFor.cmd = (byte) random(0, 2);
            if ((byte) random(0, 2))_cmdFor.cmd = BELOK_KIRI;
            else _cmdFor.cmd = BELOK_KANAN;
            _Robot->reset();         
          }
          _Robot->actionFor(_cmdFor);
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }
  
  private:
    String  _id;
    cmdRobot _cmdFor;
    sensorRobot _sensorRobot;
    freeRobot _freeRobot;
    robot2W *_Robot;
};

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\Robot2wRemoteCmd.ino"
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

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_MenuRobot.ino"
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

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_ModeAction.ino"
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

#line 1 "f:\\DATA\\Project\\Izan\\robot2wCls\\_main.ino"
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

