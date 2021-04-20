/*
  locPan.h - Library untuk locPan
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef locPan_h
#define locPan_h

#include  "Arduino.h"
#include  "src\model\model.h"
#include  "src\compDevices\viewLcd.h"
#include  "src\compDevices\keyPad.h"

class LocPan
{
  public:
    static unsigned char cmdInNbr;
    static unsigned char getCmdInNbr(){
      return cmdInNbr;
    }
    LocPan(String);//constructor
    void attachCmdIn(command*);//Pasang command, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachView(ViewLcd*);//Pasang View, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachModelMenu(AccessDataMenu*);//Pasang Model menu, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachModelParameter(AccessParam*);//Pasang Model Parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void updateParameter();
    void menu();
    int getException();
    void init();
    void info();

  private:
    String _id;
    AccessDataMenu *_accessMenu;
    AccessParam *_accessParameter;
    command *_cmdInput[MAX_CMD_INPUT];
    ViewLcd    *_view;
    param _dataParam;

    char _prevCmd, _prevLocalCmd;
    int _modeMenu = MODE_MAIN;
    int _menuIndex, _prevMenuIndex, _paramIndex, _prevParamIndex;
    int _exception = NO_EXCEPTION;
    boolean _isParamChanged, _isSaved;

    void _viewMenu(int);//Tampilkan Menu ke LCD sesuai index-menu
    void _sendMenu(int);//Kirim Menu ke serial port sesuai index-menu
    void _viewParameter(int);//Tampilkan Parameter ke LCD sesuai index-Parameter
    void _sendParameter(int);//Kirim Parameter ke serial port sesuai index-Parameter
    int _increaseIndex();
    int _decreaseIndex();
    void _increaseParameter(int);
    void _decreaseParameter(int);
    char _getCommand();
    void _menuMain(char);
    void _menuLocal(char);
    void _menuGym(char);
    void _menuLineTracer(char);
    void _menuAvoider(char);
    void _menuParameter(char);
    void _menuChangeParameter(char);
    void _initPrevIndex();
    void _setupParameter();
    void _setupMenu();
};//end of class
#endif
