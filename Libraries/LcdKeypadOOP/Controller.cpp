/*
  Controller.h - Library untuk Controller
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 2021
*/

/* Dependencies */
#include "Controller.h"

//global function
Controller::Controller(String id):_id(id){
  _menuIndex = 0;
  _modeMenu = MODE_MENU_UTAMA;
  _paramIndex = PARAMETER_VALUE;
  _prevMenuIndex = MAX_MENU + 1;//just put number greather than MAX_MENU
  _prevParamIndex = PARAMETER_INCREMENT + 1;//just put number greather than PARAMETER_INCREMENT
}

void Controller::attachCmdIn(command *cmdIn){
  Serial.print("Controller::attachCmdIn-");
  Serial.println(cmdInNbr);
  _cmdInput[cmdInNbr] = cmdIn;
  cmdInNbr++;
}

void Controller::setMenuIndex(int index){
    if ((index > 0) && (index < AccessDataMenu::getmenuNbr())) _menuIndex = index;
}

int Controller::getMenuIndex(){
  return _menuIndex;
}

int Controller::getParameterIndex(){
  return _paramIndex;
}

void Controller::pasangModelMenu(AccessDataMenu *accessMenu){
    Serial.println("Controller::pasangModelMenu");
    _accessMenu = accessMenu;
  }
 
void Controller::pasangModelParameter(AccessParameter *accessParameter){
    Serial.println("Controller::pasangModelParameter");
    _accessParameter = accessParameter;
  }
 
void Controller::pasangView(View *view){
    Serial.println("Controller::pasangView");
    _view = view;
  }

//private function
char Controller::_getCommand(){
  char rawCmd = NO_KEY;
  for (int i=0; i < this->cmdInNbr; i++){
      rawCmd = _cmdInput[i]->ambilCode();
      if (rawCmd != NO_KEY){
          _prevCmd = rawCmd;
          break;
      }
  }
  return rawCmd;
}

void Controller::_setCommand(char cmd){
  this->_prevCmd = cmd;
}

int Controller::_naikkanIndex(){
  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        if (_menuIndex < (AccessDataMenu::getmenuNbr()-1)) _menuIndex++;
        else _menuIndex = 0;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex < PARAMETER_INCREMENT) _paramIndex++;
        else _paramIndex = PARAMETER_VALUE;
        return _paramIndex;
        break;
      default:
          break;
    }
}
 
int Controller::_turunkanIndex(){
  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        if (_menuIndex > 0) _menuIndex--;
        else _menuIndex = AccessDataMenu::getmenuNbr()-1;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex < PARAMETER_INCREMENT) _paramIndex--;
        else _paramIndex = PARAMETER_VALUE;
        return _paramIndex;
        break;
      default:
          break;
    }
}
 
void Controller::_tampilkanMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      if (tempMenu.id > 0){
        _view->hapusLayar();//hapus semua tampilan dulu
        _view->tampilkanPesan(0,0,tempMenu.pesan1);//pesan1 pada baris 1
        _view->tampilkanPesan(1,0,tempMenu.pesan2);//pesan2 pada baris 2
        _prevMenuIndex = index;
      }
    }
  }

void Controller::_kirimMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      if (tempMenu.id > 0){
        Serial.println(tempMenu.id);
        Serial.println(tempMenu.pesan1);
        Serial.println(tempMenu.pesan2);
        //_prevMenuIndex = index;
      }
    }
  }

void Controller::_tampilkanParameter(parameter dataParam, int index){
  String paramStr;
  boolean isUpdate = false;

  //check if display need to be updated
  if(_prevParamIndex != index){
    _prevParamIndex = index;
    if (this->_modeMenu == MODE_MENU_PARAMETER) isUpdate = true;
  } 
  else{
    if (this->_isParamChanged)isUpdate = true;
    this->_isParamChanged = false;
  }

  if(isUpdate){
    isUpdate = false;
    _prevParamIndex = index;
    _view->hapusLayar();//hapus semua tampilan dulu

    if(this->_modeMenu == MODE_MENU_PARAMETER){
      _view->tampilkanPesan(0,0,_accessParameter->toString(dataParam));
    }
    else if(this->_modeMenu == MODE_UBAH_PARAMETER){
      _view->tampilkanPesan(0,0,"Change Parameter");
    }

    switch (index)
    {
    case PARAMETER_VALUE:
      paramStr = "Value : ";
      paramStr =  String(paramStr + dataParam.value);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_RANGE:
      paramStr = "LoRng : ";
      paramStr =  String(paramStr + dataParam.lowRange);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_RANGE:
      paramStr = "HiRng : ";
      paramStr =  String(paramStr + dataParam.highRange);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_LIMIT:
      paramStr = "LoLmt : ";
      paramStr =  String(paramStr + dataParam.lowLimit);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_LIMIT:
      paramStr = "HiLmt : ";
      paramStr =  String(paramStr + dataParam.highLimit);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    case PARAMETER_INCREMENT:
      paramStr = "Incr : ";
      paramStr =  String(paramStr + dataParam.increment);
      _view->tampilkanPesan(1,0,paramStr);//pesan pada baris 2
      break;
    
    default:
      break;
    }
  }
}

void Controller::_kirimParameter(parameter dataParam, int index){
  
  String paramStr;
  boolean isUpdate = false;

  //check if display need to be updated
  if(_prevParamIndex != index){
    //_prevParamIndex = index;
    if (this->_modeMenu == MODE_MENU_PARAMETER) isUpdate = true;
  } 
  else{
    if (this->_isParamChanged)isUpdate = true;
    //this->_isParamChanged = false;
  }

  if(isUpdate){
    if(this->_modeMenu == MODE_MENU_PARAMETER){
      Serial.println(_accessParameter->toString(dataParam));
    }
    else if(this->_modeMenu == MODE_UBAH_PARAMETER){
      Serial.println("Change Parameter");
    }

    switch (index)
    {
      case PARAMETER_VALUE:
        paramStr = "Value : ";
        paramStr =  String(paramStr + dataParam.value);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_RANGE:
        paramStr = "LoRng : ";
        paramStr =  String(paramStr + dataParam.lowRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_RANGE:
        paramStr = "HiRng : ";
        paramStr =  String(paramStr + dataParam.highRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_LIMIT:
        paramStr = "LoLmt : ";
        paramStr =  String(paramStr + dataParam.lowLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_LIMIT:
        paramStr = "HiLmt : ";
        paramStr =  String(paramStr + dataParam.highLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_INCREMENT:
        paramStr = "Incr : ";
        paramStr =  String(paramStr + dataParam.increment);
        Serial.println(paramStr);
        break;
      
      default:
        break;
      }
    }
  }

void Controller::menu(){
  parameter paramData = _accessParameter->getParameter(this->getMenuIndex());
  char key = this->_getCommand();

  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        this->_menuUtama(key);
        break;
      case MODE_MENU_PARAMETER:
        this->_menuParameter(paramData, key);
        break;
      case MODE_UBAH_PARAMETER:
        this->_menuUbahParameter(paramData, key);
        break;
      case 'N':
      default:
          break;
    }
}

void Controller::_menuUtama(char key){
  String keyStr = "";
  dataMenu menuData;
  int idx;//for index

  if(this->_menuIndex == 0){
    this->_kirimMenu(this->_menuIndex);//kirim menu ke serial port
    this->_tampilkanMenu(this->_menuIndex);//tampilkan menu ke lcd
  }

  switch (key) // See which menu item is selected and execute that correS_Pond function
    {
        case 'S':
          //Tempatkan menu di sini
          keyStr = "Select";
          _view->tampilkanPesan(0,0,"-Diag LcdKeypad-");//tampilkan pesan pada baris 0, kolom 0              
          _view->tampilkanPesan(1,0,"Keypad : ");//tampilkan pesan pada baris 1, kolom 0              
          _view->tampilkanPesan(1,9,keyStr);//tampilkan pesan pada baris 1, kolom 10
          break;
        case 'U':
          //naikkan index
          idx = this->_naikkanIndex();
          this->_kirimMenu(idx);//kirim menu ke serial port
          this->_tampilkanMenu(idx);//tampilkan menu ke lcd
          break;
        case 'D':
          //Turunkan index
          idx = this->_turunkanIndex();
          this->_kirimMenu(idx);//kirim menu ke serial port
          this->_tampilkanMenu(idx);//tampilkan menu ke lcd
          break;
        case 'L':
          //Tempatkan menu di sini
          keyStr = "Left  ";
          _view->tampilkanPesan(0,0,"-Diag LcdKeypad-");//tampilkan pesan pada baris 0, kolom 0              
          _view->tampilkanPesan(1,0,"Keypad : ");//tampilkan pesan pada baris 1, kolom 0              
          _view->tampilkanPesan(1,9,keyStr);//tampilkan pesan pada baris 1, kolom 10
          break;
        case 'R':
          //ke menu parameter
          menuData = _accessMenu->read(this->_menuIndex);
          if (menuData.hasParameter){
            _modeMenu = MODE_MENU_PARAMETER;
            this->_paramIndex = PARAMETER_VALUE;
          }
          else{
            keyStr = "Right ";
            _view->tampilkanPesan(0,0,"-Diag LcdKeypad-");//tampilkan pesan pada baris 0, kolom 0              
            _view->tampilkanPesan(1,0,"Keypad : ");//tampilkan pesan pada baris 1, kolom 0              
            _view->tampilkanPesan(1,9,keyStr);//tampilkan pesan pada baris 1, kolom 10
          }
          break;
        case 'N':
        default:
          break;
    }
}

void Controller::_menuParameter(parameter paramData, char key){
  String keyStr = "";
  int idx;//for index

  if(this->_paramIndex == PARAMETER_VALUE){
    idx = this->_paramIndex;
    this->_kirimParameter(paramData,idx);//kirim parameter ke serial port
    this->_tampilkanParameter(paramData,idx);//tampilkan parameter ke lcd
  }

  switch (key)
    {
      case 'S':
        //Tempatkan menu di sini
        keyStr = "Select";
        _view->tampilkanPesan(0,0,"-Diag LcdKeypad-");//tampilkan pesan pada baris 0, kolom 0              
        _view->tampilkanPesan(1,0,"Keypad : ");//tampilkan pesan pada baris 1, kolom 0              
        _view->tampilkanPesan(1,9,keyStr);//tampilkan pesan pada baris 1, kolom 10
        break;
      case 'U':
        //Naikkan Index
        idx = this->_naikkanIndex();
        this->_kirimParameter(paramData,idx);//kirim parameter ke serial port
        this->_tampilkanParameter(paramData,idx);//tampilkan parameter ke lcd
        break;
      case 'D':
        //Naikkan Index
        idx = this->_turunkanIndex();
        this->_kirimParameter(paramData,idx);//kirim parameter ke serial port
        this->_tampilkanParameter(paramData,idx);//tampilkan parameter ke lcd
        break;
      case 'L':
        //kembali ke menu utama
        _modeMenu = MODE_MENU_UTAMA;
        this->_menuIndex = 0;
        //this->_menuUtama(NO_KEY);
        break;
      case 'R':
        //ke menu ubah parameter
        _modeMenu = MODE_UBAH_PARAMETER;
        //this->_menuUbahParameter(paramData, NO_KEY);
        break;
      case 'N':
      default:
        break;
    }
}

void Controller::_menuUbahParameter(parameter paramData, char key){
  String keyStr = "";
  int idx, idxParam;
  switch (key)
    {
      case 'S':
        //save change to parameter
        if (this->_isSaved){
          this->_isSaved = false;//false is saved
          idxParam = this->_accessParameter->getIndexParameter(paramData);
          this->_accessParameter->setParameter(idxParam,paramData);
          _view->tampilkanPesan(0,0,"Parameter saved");//tampilkan pesan pada baris 0, kolom 0              
          Serial.println("Parameter saved");          
        }
        break;
      case 'U':
        //Naikkan parameter
        idx = this->_paramIndex;
        paramData = this->_accessParameter->increaseParameter(paramData,idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_kirimParameter(paramData, idx);//kirim parameter ke serial port
        this->_tampilkanParameter(paramData, idx);//tampilkan parameter ke lcd
        break;
      case 'D':
        //turunkan parameter
        idx = this->_paramIndex;
        paramData = this->_accessParameter->decreaseParameter(paramData,idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_kirimParameter(paramData, idx);//kirim parameter ke serial port
        this->_tampilkanParameter(paramData, idx);//tampilkan parameter ke lcd
        break;
      case 'L':
        //kembali ke menu utama
        _modeMenu = MODE_MENU_PARAMETER;
        //this->_menuParameter(paramData, NO_KEY);
        break;
      case 'R':
        //ke menu ubah parameter
        keyStr = "Select";
        _view->tampilkanPesan(0,0,"-Diag LcdKeypad-");//tampilkan pesan pada baris 0, kolom 0              
        _view->tampilkanPesan(1,0,"Keypad : ");//tampilkan pesan pada baris 1, kolom 0              
        _view->tampilkanPesan(1,9,keyStr);//tampilkan pesan pada baris 1, kolom 10
        break;
      case 'N':
      default:
        break;
    }
}