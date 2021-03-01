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
