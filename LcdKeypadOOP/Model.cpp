/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
*/

#include "Model.h"

//AccessDataMenu - Class
AccessDataMenu::AccessDataMenu(String id):_id(id){}

void AccessDataMenu::add(dataMenu data){
  this->_dataMenu[menuNbr] = data;
  menuNbr++;
}

dataMenu AccessDataMenu::read(int index){
  return _dataMenu[index];
}

//Parameter - Class
AccessParameter::AccessParameter(String id):_id(id){}

void AccessParameter::add(parameter param){
  this->_parameter[paramNbr] = param;
  paramNbr++;
}

String AccessParameter::toString(parameter paramData){
  String str = paramData.id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + paramData.unit);
  if (paramData.lowAlarm){
    alm = "(L)";
  }
  if (paramData.highAlarm){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

void AccessParameter::setParameter(int index, parameter data){
  this->_parameter[index] = data;
}

parameter AccessParameter::getParameter(int index){
  //matching with index menu
   for (int i=0; i <= this->paramNbr; i++){
      if (this->getIndexMenu(i) == index)return this->_parameter[i];
   } 
}

int AccessParameter::getIndexMenu(int index){
  return this->_parameter[index].indexMenu;
}

int AccessParameter::getIndexParameter(parameter paramData){
  int i = 0;
  for (i = 0; i < this->paramNbr; i++)
  {
    if (paramData.id == this->_parameter[i].id)
    {
      break;
    }  
  }
  return i;
}

void AccessParameter::_checkAlarm(parameter paramData){
  //Alarm Low evaluation
  paramData.lowAlarm = false;
  if (paramData.value <= paramData.lowAlarm) {
    paramData.lowAlarm = true;
    return;
  }

  //Alarm High evaluation
  paramData.highAlarm = false;
  if (paramData.value >= paramData.highAlarm) {
    paramData.highAlarm = true;
    return;
  }
}

parameter AccessParameter::increaseParameter(parameter paramData, int idParam){
  float percentInc = ((paramData.increment)/100);
  float range = (paramData.highRange - paramData.lowRange);
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_VALUE:
      tempVal = paramData.value = paramData.value + increment;
      if(tempVal < paramData.highRange) paramData.value = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_LOW_RANGE:
      tempVal = paramData.lowRange + increment;
      if(tempVal < paramData.lowLimit) paramData.lowRange = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = paramData.highRange + increment;
      if(tempVal < paramData.highRange) paramData.highRange = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = paramData.lowLimit + increment;
      if(tempVal < paramData.highLimit) paramData.lowLimit = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = paramData.highLimit + increment;
      if(tempVal < paramData.highRange) paramData.highLimit = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_INCREMENT:
      paramData.increment = paramData.increment + paramData.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;
    return paramData;
  }
}

parameter AccessParameter::decreaseParameter(parameter paramData, int idParam){
  float percentInc = ((paramData.increment)/100);
  float range = (paramData.highRange - paramData.lowRange);
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_VALUE:
      tempVal = paramData.value = paramData.value - increment;
      if(tempVal > paramData.lowRange) paramData.value = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_LOW_RANGE:
      tempVal = paramData.lowRange - increment;
      if(tempVal > paramData.lowRange) paramData.lowRange = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = paramData.highRange - increment;
      if(tempVal > paramData.highLimit) paramData.highRange = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = paramData.lowLimit - increment;
      if(tempVal > paramData.lowLimit) paramData.lowLimit = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = paramData.highLimit - increment;
      if(tempVal > paramData.lowLimit) paramData.highLimit = tempVal;
      this->_checkAlarm(paramData);
      break;
    
    case PARAMETER_INCREMENT:
      paramData.increment = paramData.increment - paramData.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;

    return paramData;
  }
}

