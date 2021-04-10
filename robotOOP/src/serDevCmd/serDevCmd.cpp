/*
 * lihat header file command.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "serDevCmd.h"


serialCmd::serialCmd(String id): _id(id){
}

void serialCmd::init(){}

void serialCmd::info(){
    Serial.println("serialCmd::info()");

    Serial.print("_id");
    Serial.println(_id);

    Serial.println("<----->");
}

char serialCmd::getCode(){
  char serialCmd = NO_KEY;
  if (Serial.available() > 0) {
      serialCmd = Serial.read();
      if (!serialCmd::isValid(serialCmd))serialCmd = NO_KEY;
  }  
  return serialCmd;
}

bool serialCmd::isValid(char cmdVal){
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

bluetoothCmd::bluetoothCmd(String id): _id(id){
}

void bluetoothCmd::init(){}

void bluetoothCmd::info(){
    Serial.println("bluetoothCmd::info()");

    Serial.print("_id");
    Serial.println(_id);

    Serial.println("<----->");
}

char bluetoothCmd::getCode(){
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

bool bluetoothCmd::isValid(char cmdVal){
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

