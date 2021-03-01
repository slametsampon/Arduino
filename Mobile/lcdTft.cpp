/*
 * lihat header file lcdTft.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "lcdTft.h"

//lcdTitle harus di-deklarasi di sini, jika tidak (ERRORR !!!!!!)
char* lcdTitle[] = {"ROBOT CERDAS", "MODE REMOTE", "MODE SENAM",
                        "MODE RECORD", "MODE TRACKING", "MODE A.GARIS", "MODE A.JARAK"};

lcdTft::lcdTft (String id):_id(id){}

String lcdTft::getId(){return _id;}

void lcdTft::init(){
    uint16_t ID = _tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    _tft.begin(ID);
    _tft.setRotation(0);            //PORTRAIT
    _tft.fillScreen(BLACK);
}

void lcdTft::buildComponent(){
    _remoteBtn.initButton(&_tft,  60, 125, 110, 60, WHITE, CYAN, BLACK, "REMOTE", 2);
    _recordBtn.initButton(&_tft,  180, 125, 110, 60, WHITE, CYAN, BLACK, "RECORD", 2);
    _senamBtn.initButton(&_tft,  60, 195, 110, 60, WHITE, CYAN, BLACK, "SENAM", 2);
    _trackingBtn.initButton(&_tft,  180, 195, 110, 60, WHITE, CYAN, BLACK, "TRACKING", 2);
    _autoGarisBtn.initButton(&_tft,  60, 270, 110, 60, WHITE, CYAN, BLACK, "A.GARIS", 2);
    _autoJarakBtn.initButton(&_tft,  180, 270, 110, 60, WHITE, CYAN, BLACK, "A.JARAK", 2);
    _mainBtn.initButton(&_tft,  120, 270, 140, 60, WHITE, CYAN, BLACK, "MENU UTAMA", 2);   
}

void lcdTft::displayText(int xPos, int yPos, int lebar, int tinggi,String strVal){
    _tft.fillRect(xPos,yPos,lebar,tinggi,BLACK);//0,100,240,120
    _tft.setTextColor(WHITE);
    _tft.setTextSize(2);
    _tft.setCursor(xPos, yPos);
    _tft.println(strVal);  
}

void lcdTft::displayPage(char mode){
    switch (mode){
        case MENU_UTAMA: 
            this->_displayTitle(lcdTitle[0]);
            _tft.setTextColor(WHITE);
            _tft.setTextSize(1);
            _tft.setCursor(150, 67);
            _tft.print("By : Izan");

            //draw components        
            _remoteBtn.drawButton(false);
            _senamBtn.drawButton(false);
            _recordBtn.drawButton(false);
            _trackingBtn.drawButton(false);
            _autoGarisBtn.drawButton(false);      
            _autoJarakBtn.drawButton(false);      
        break; 
        case REMOTE:
            this->_displayTitle(lcdTitle[1]);
            _mainBtn.drawButton(false);          
        break;
        case SENAM:
            this->_displayTitle(lcdTitle[2]);
            _mainBtn.drawButton(false);          
        break;
        case RECORD:
            this->_displayTitle(lcdTitle[3]);
            _mainBtn.drawButton(false);          
        break;
        case TRACKING:
            this->_displayTitle(lcdTitle[4]);
            _mainBtn.drawButton(false);          
        break;
        case AUTO_GARIS:
            this->_displayTitle(lcdTitle[5]);
            _mainBtn.drawButton(false);          
        break;
        case AUTO_JARAK:
            this->_displayTitle(lcdTitle[6]);
            _mainBtn.drawButton(false);          
        break;
        default:
        break;
    }
}

char lcdTft::getCommand(char mode){
    char rawCmd = INV_CMD;
    bool down = this->_touchGetXY();
    delay(100);
    if (down){
        switch (mode){
            case MENU_UTAMA: 
                rawCmd = this->_getRootCmd(down);
            break; 
            case REMOTE:
            case SENAM:
            case RECORD:
            case TRACKING:
            case AUTO_GARIS:
            case AUTO_JARAK:
                rawCmd = this->_getSubCmd(down);
            break;
            default:
            break;
        }
    }
    if (rawCmd == INV_CMD) rawCmd = _prevCmd;
    return rawCmd;
}


void lcdTft::_displayTitle(char titleVal[15]){  
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

bool lcdTft::_touchGetXY(){
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

char lcdTft::_getRootCmd(bool lcdPress){
    char rawCmd = INV_CMD;
    _remoteBtn.press(lcdPress && _remoteBtn.contains(_pixel.x, _pixel.y));
    _senamBtn.press(lcdPress && _senamBtn.contains(_pixel.x, _pixel.y));
    _recordBtn.press(lcdPress && _recordBtn.contains(_pixel.x, _pixel.y));
    _trackingBtn.press(lcdPress && _trackingBtn.contains(_pixel.x, _pixel.y));
    _autoGarisBtn.press(lcdPress && _autoGarisBtn.contains(_pixel.x, _pixel.y));
    _autoJarakBtn.press(lcdPress && _autoJarakBtn.contains(_pixel.x, _pixel.y));
    // it jus pressed moment        
    if (_remoteBtn.justPressed()) {
    _remoteBtn.drawButton(true);
    rawCmd = REMOTE;
    }

    if (_senamBtn.justPressed()) {
    _senamBtn.drawButton(true);
    rawCmd = SENAM;
    }
    if (_recordBtn.justPressed()) {
    _recordBtn.drawButton(true);
    rawCmd = RECORD;
    }
    if (_trackingBtn.justPressed()) {
    _trackingBtn.drawButton(true);
    rawCmd = TRACKING;
    }
    if (_autoGarisBtn.justPressed()) {
    _autoGarisBtn.drawButton(true);
    rawCmd = AUTO_GARIS;
    }      
    if (_autoJarakBtn.justPressed()) {
    _autoJarakBtn.drawButton(true);
    rawCmd = AUTO_JARAK;
    } 
    return rawCmd;     
}

char lcdTft::_getSubCmd(bool lcdPress){
    char rawCmd = INV_CMD;
    //if (_mainBtn.justReleased())_mainBtn.drawButton();
    _mainBtn.press(lcdPress && _mainBtn.contains(_pixel.x, _pixel.y));
    if (_mainBtn.justPressed()){
    _mainBtn.drawButton(true);                
    rawCmd = MENU_UTAMA;
    }
    return rawCmd;
}
