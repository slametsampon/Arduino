/*
  ViewLcd.h - Library untuk ViewLcd
  Ini adalah bagian dari MVC (Model ViewLcd Control) pattern design
  Dibuat Oleh : Sam Feb 17, 2021
*/
#ifndef ViewLcd_h
#define ViewLcd_h

#include "Arduino.h"
#include <LiquidCrystal.h>//for LCD

const int LCD_ROWS = 2;
const int LCD_COLUMNS = 16;

class ViewLcd
{
  public:
    ViewLcd(LiquidCrystal);//constructor
    void viewMessage(int, int, String);//Tampilkan Pesan pada lcd
    void clearView();//Hapus tampilan pada lcd
  private:
    int _kolom, _baris;
    LiquidCrystal _lcd;
    String _id;
};//end of class
#endif
