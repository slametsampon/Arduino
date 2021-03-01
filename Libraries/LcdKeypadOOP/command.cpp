/*
 * lihat header file command.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "command.h"

bool command::isValid(char cmdVal){
  bool flVal = false;
  switch (cmdVal){
    
    //Keypad validation
    case UP: 
    case DOWN:
    case RIGHT:
    case LEFT:
    case SELECT:
      flVal = true;
      break;
    
    //Other validation bluetooth, esp etc...
    default:
      break;
  }
  return flVal;
}

serialCmd::serialCmd(String id): _id(id){
}

char serialCmd::ambilCode(){
  char serialCmd = NO_KEY;
  if (Serial.available() > 0) {
      serialCmd = Serial.read();
      if (!command::isValid(serialCmd))serialCmd = NO_KEY;
  }  
  return serialCmd;
}

bluetoothCmd::bluetoothCmd(String id): _id(id){
}

char bluetoothCmd::ambilCode(){
  char bluetoothCmd = NO_KEY;
  /*
  if (Serial1.available() > 0) {
      bluetoothCmd = Serial1.read();
      if (bluetoothCmd != STOP_BT){
        if (!command::isValid(bluetoothCmd))bluetoothCmd = NO_KEY;
      }
  }
  */
  return bluetoothCmd;
}
