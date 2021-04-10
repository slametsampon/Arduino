/*
 * lihat header file ViewLcd.h lebih detail
 * extention file harus .cpp bukan .CPP
  Ini adalah bagian dari MVC (Model ViewLcd Control) pattern design
 * Feb 13, 2021 by Sam
 */

/* Dependencies */
#include "viewLcd.h"

ViewLcd::ViewLcd(LiquidCrystal lcd):_lcd(lcd){
    _lcd.begin(LCD_COLUMNS, LCD_ROWS);  
}

void ViewLcd::viewMessage(int baris, int kolom, String pesan){
    _lcd.setCursor(kolom,baris);
    _lcd.print(pesan);
  }

void ViewLcd::clearView(){
  _lcd.clear();
}
