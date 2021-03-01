/*
  View.h - Library untuk View
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 17, 2021
*/
#ifndef View_h
#define View_h

#include "Arduino.h"
#include <LiquidCrystal.h>//for LCD

const int LCD_ROWS = 2;
const int LCD_COLUMNS = 16;

class View
{
  public:
    View(LiquidCrystal);//constructor
    void hapusBaris(int, int);//hapus display
    void tampilkanPesan(int, int, String);//Tampilkan Pesan pada lcd
    void hapusLayar();//Hapus tampilan pada lcd
  private:
    int _kolom, _baris;
    LiquidCrystal _lcd;
    String _id;
};//end of class
#endif
