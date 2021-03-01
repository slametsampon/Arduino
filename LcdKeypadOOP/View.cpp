/*
 * lihat header file View.h lebih detail
 * extention file harus .cpp bukan .CPP
  Ini adalah bagian dari MVC (Model View Control) pattern design
 * Feb 13, 2021 by Sam
 */

/* Dependencies */
#include "View.h"

View::View(LiquidCrystal lcd):_lcd(lcd){
    _lcd.begin(LCD_COLUMNS, LCD_ROWS);  
}

void View::hapusBaris(int baris, int kolom){
    _lcd.setCursor(kolom,baris);
    _lcd.print("                ");//print 16 blank
  }

void View::tampilkanPesan(int baris, int kolom, String pesan){
    _lcd.setCursor(kolom,baris);
    _lcd.print(pesan);
  }

void View::hapusLayar(){
  _lcd.clear();
}
