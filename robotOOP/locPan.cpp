/*
  locPan.h - Library untuk LocPan
  Dibuat Oleh : Sam March 18, 2021
*/

/* Dependencies */
#include "locPan.h"

//global function
LocPan::LocPan(String id):_id(id){
  this->init();
}

void LocPan::init(){

  _modeMenu = MODE_MAIN;
  _menuIndex = 0;

  _prevCmd = NO_KEY;
  _prevLocalCmd = NO_KEY;

  this->_initPrevIndex();

  for (int i=0; i < this->cmdInNbr; i++){
      _cmdInput[i]->init();
  }

  this->_setupMenu();
  //this->_setupParameter();

}

void LocPan::info(){
  Serial.println("LocPan::info()");
  Serial.print("_id : ");
  Serial.println(_id);

  //attachment info
  Serial.println("Attachment :");
  for (int i=0; i < this->cmdInNbr; i++){
      _cmdInput[i]->info();
  }

  _view->info();
  _accessMenu->info();
}

void LocPan::attachCmdIn(command *cmdIn){
  Serial.print("LocPan::attachCmdIn-");
  Serial.println(cmdInNbr);
  _cmdInput[cmdInNbr] = cmdIn;
  cmdInNbr++;
}

void LocPan::attachView(ViewLcd *view){
    Serial.println("LocPan::attachView(ViewLcd *view)");
    _view = view;
  }

void LocPan::attachModelMenu(AccessDataMenu *accessMenu){
    Serial.println("LocPan::attachModelMenu(AccessDataMenu *accessMenu)");
    _accessMenu = accessMenu;
  }
 
void LocPan::attachModelParameter(AccessParam *accessParameter){
    Serial.println("LocPan::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 
int LocPan::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void LocPan::updateParameter(){
  _dataParam = _accessParameter->getParam();

}

void LocPan::menu(){

  char key = this->_getCommand();

  switch (_modeMenu){
    case MODE_MAIN:
      this->_menuMain(key);
      break;

    case MODE_LOCAL:
      //this->_menuParameter(key);
      break;

    case MODE_REMOTE:
      //this->_menuChangeParameter(key);
      break;

    case MODE_GYM:
      //this->_menuChangeParameter(key);
      break;
      
    case MODE_LINE_TRACER:
      //this->_menuChangeParameter(key);
      break;
      
    case MODE_AVOIDER:
      //this->_menuChangeParameter(key);
      break;
      
    case 'N':
    default:
        break;
  }
}

//private function

void LocPan::_initPrevIndex(){
  _prevMenuIndex = DEFAULT_INDEX;//default value
  _prevParamIndex = DEFAULT_INDEX;//default value
}

void LocPan::_menuMain(char key){
  dataMenu menuData;
  int idx;//for index

  if(this->_menuIndex == 0){
    this->_sendMenu(this->_menuIndex);//kirim menu ke serial port
    this->_viewMenu(this->_menuIndex);//tampilkan menu ke lcd
  }

  switch (key) // See which menu item is selected and execute that correS_Pond function
    {
      case SELECT:
        //Tempatkan menu di sini
        break;

      case UP:
        //naikkan index
        idx = this->_increaseIndex();
        this->_sendMenu(idx);//kirim menu ke serial port
        this->_viewMenu(idx);//tampilkan menu ke lcd
        break;

      case DOWN:
        //Turunkan index
        idx = this->_decreaseIndex();
        this->_sendMenu(idx);//kirim menu ke serial port
        this->_viewMenu(idx);//tampilkan menu ke lcd
        break;

      case LEFT:
        //Tempatkan menu di sini
        break;

      case RIGHT:
        if (idx == MODE_LOCAL){
          _exception = LOCAL_MODE_EXCEPTION;
          this->_menuLocal(SELECT);//S : Stop
        }
        break;

      case NO_KEY://No Key
      default:
        break;
    }
}

void LocPan::_menuLocal(char key){

  _view->viewMessage(0,0,"LOCAL MENU");
  switch (key) // See which menu item is selected and execute that correS_Pond function
    {
      case SELECT:
        if (_prevLocalCmd == SELECT){
          _exception = MAIN_MODE_EXCEPTION;
          _modeMenu = MODE_MAIN;
          _menuIndex = 0;
          this->menu();
        }
        else{
          _view->viewMessage(1,0,"Stop");
        }

        break;

      case UP:
        //naikkan index
        break;

      case DOWN:
        //Turunkan index
        break;

      case LEFT:
        //Tempatkan menu di sini
        break;

      case RIGHT:
        //ke menu parameter
        break;

      case NO_KEY://No Key
      default:
        break;
    }
}

char LocPan::_getCommand(){
  char rawCmd = NO_KEY;
  for (int i=0; i < this->cmdInNbr; i++){
      rawCmd = _cmdInput[i]->getCode();
      if (rawCmd != NO_KEY){
          _prevCmd = rawCmd;
          break;
      }
  }
  return rawCmd;
}

void LocPan::_viewMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      _view->clearView();//hapus semua tampilan dulu
      _prevMenuIndex = index;
      _view->viewMessage(0,0,"SMART MOBILE ROBOT");
      _view->viewMessage(1,0,tempMenu.Messages);
    }
  }

void LocPan::_sendMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      Serial.print("index : ");
      Serial.println(index);
      Serial.print("tempMenu.Messages : ");
      Serial.println(tempMenu.Messages);

      //_prevMenuIndex = index;
    }
  }

int LocPan::_increaseIndex(){
  switch (_modeMenu)
    {
      case MODE_MAIN:
        if (_menuIndex < (AccessDataMenu::getmenuNbr()-1)) _menuIndex++;
        else _menuIndex = 0;
        return _menuIndex;
        break;

      default:
          break;
    }
}
 
int LocPan::_decreaseIndex(){
  switch (_modeMenu)
    {
      case MODE_MAIN:
        if (_menuIndex > 0) _menuIndex--;
        else _menuIndex = AccessDataMenu::getmenuNbr()-1;
        return _menuIndex;
        break;
        
      default:
          break;
    }
}

void LocPan::_setupMenu(){
  dataMenu  dtMenu;

  Serial.println("LocPan::_setupMenu()");

  dtMenu.Messages="Menu Local";
  _accessMenu->add(dtMenu);

  dtMenu.Messages="Menu Remote";
  _accessMenu->add(dtMenu);

  dtMenu.Messages="Menu Gym";
  _accessMenu->add(dtMenu);

  dtMenu.Messages="Menu Line Tracer";
  _accessMenu->add(dtMenu);

  dtMenu.Messages="Menu Avoider";
  _accessMenu->add(dtMenu);

}