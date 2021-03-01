/*
 * lihat header file command.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "command.h"

bool command::isValid(char cmdVal){
  bool flVal = false;
  switch (cmdVal){
      case MENU_UTAMA: 
      case REMOTE:
      case SENAM:
      case RECORD:
      case TRACKING:
      case AUTO_GARIS:
      case AUTO_JARAK:
      case STOP_REMOTE://all stop commands
      case GEAR0: 
      case GEAR1: 
      case GEAR2: 
      case GEAR3: 
      case GEAR4: 
      case GEAR5: 
      case GEAR6: 
      case MAJU: 
      case MUNDUR: 
      case BELOK_KIRI: 
      case BELOK_KANAN: 
      case MAJU_KIRI: 
      case MAJU_KANAN: 
      case MUNDUR_KIRI: 
      case MUNDUR_KANAN: 
      case BERHENTI: 
        flVal = true;
      break;
      default:
      break;
  }
  return flVal;
}

serialCmd::serialCmd(String id): _id(id){
}
char serialCmd::getCommand(){
  char serialCmd = INV_CMD;
  if (Serial.available() > 0) {
      serialCmd = Serial.read();
      if (!command::isValid(serialCmd))serialCmd = INV_CMD;
  }  
  return serialCmd;
}

bluetoothCmd::bluetoothCmd(String id): _id(id){
}
char bluetoothCmd::getCommand(){
  char bluetoothCmd = INV_CMD;
  if (Serial1.available() > 0) {
      bluetoothCmd = Serial1.read();
      if (bluetoothCmd != STOP_BT){
        if (!command::isValid(bluetoothCmd))bluetoothCmd = INV_CMD;
      }
  }
  return bluetoothCmd;
}
