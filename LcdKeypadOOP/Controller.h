/*
  Controller.h - Library untuk Controller
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Model.h"
#include "View.h"
#include "KeyPad.h"
#include "command.h"

const int MODE_MENU_UTAMA = 1;
const int MODE_MENU_PARAMETER = 2;
const int MODE_UBAH_PARAMETER = 3;

class Controller
{
  public:
    static unsigned char cmdInNbr;
    static unsigned char getCmdInNbr(){
      return cmdInNbr;
    }
    Controller(String);//constructor
    void attachCmdIn(command*);//Pasang command, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void pasangModelMenu(AccessDataMenu*);//Pasang Model menu, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void pasangModelParameter(AccessParameter*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void pasangView(View*);//Pasang View, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void setMenuIndex(int);
    int getMenuIndex();
    int getParameterIndex();
    void menu();
  private:
    String _id;
    KeyPad *_keyPad;
    AccessDataMenu *_accessMenu;
    AccessParameter *_accessParameter;
    View *_view;
    int _menuIndex, _prevMenuIndex, _paramIndex, _prevParamIndex;
    command *_cmdInput[MAX_CMD_INPUT];
    char _prevCmd;
    int _modeMenu = MODE_MENU_UTAMA;

    void _tampilkanMenu(int);//Tampilkan Menu ke LCD sesuai index-menu
    void _kirimMenu(int);//Kirim Menu ke serial port sesuai index-menu
    void _tampilkanParameter(parameter, int);//Tampilkan Parameter ke LCD sesuai index-Parameter
    void _kirimParameter(parameter, int);//Kirim Parameter ke serial port sesuai index-Parameter
    int _naikkanIndex();
    int _turunkanIndex();
    char _getCommand();
    void _setCommand(char);
    void _menuUtama(char);
    void _menuParameter(parameter, char);
    void _menuUbahParameter(parameter, char);
    boolean _isParamChanged, _isSaved;
};//end of class
#endif
