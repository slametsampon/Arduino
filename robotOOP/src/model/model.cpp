#include    "model.h"

//AccessDataMenu - Class
AccessDataMenu::AccessDataMenu(String id):_id(id){}

void AccessDataMenu::add(dataMenu data){
  this->_dataMenu[menuNbr] = data;
  menuNbr++;
}

dataMenu AccessDataMenu::read(int index){
  return _dataMenu[index];
}
