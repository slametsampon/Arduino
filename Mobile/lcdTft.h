/*
  lcdTft.h - Library untuk lcdTft
  Dibuat Oleh : Sam May 2020
*/
#ifndef lcdTft_h
#define lcdTft_h

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "command.h"
#include "Arduino.h"

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

// ALL Touch panels and wiring is DIFFERENT
// copy-paste resul_ts from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT=175,TS_RT=905,TS_TOP=932,TS_BOT=200;

//class lcdTft:public command{, gave ERRORR DURING COMPILE !!!!!!
//Inheritance from other file "public command" {, gave ERRORR DURING COMPILE !!!!!!
    
class lcdTft{    
  struct touchPixel
    {
      int x;
      int y;     //Touch_getXY() updates global vars
    };
    
    public:
      lcdTft (String);
      String getId();
      void init();
      void buildComponent();
      void displayText(int xPos, int yPos, int lebar, int tinggi,String strVal);
      char getCommand(char);
      void displayPage(char);
    private:
      touchPixel  _pixel;
      boolean printDiagOK = false;      
      char _CurrMode;
      String  _id;
      char  _prevCmd;
      Adafruit_GFX_Button _mainBtn, _remoteBtn, _senamBtn, _recordBtn,
                          _trackingBtn, _autoGarisBtn, _autoJarakBtn;
      TouchScreen _ts = TouchScreen(XP, YP, XM, YM, 300);
      MCUFRIEND_kbv _tft;

      void _displayTitle(char titleVal[15]);
      char _getRootCmd(bool lcdPress);
      char _getSubCmd(bool lcdPress);
      bool _touchGetXY();
};
#endif
