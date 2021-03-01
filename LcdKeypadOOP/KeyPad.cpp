/*
 * lihat header file KeyPad.h lebih detail
 * extention file harus .cpp bukan .CPP
 * Feb 13, 2021 by Sam
 */

/* Dependencies */
#include "KeyPad.h"

KeyPad::KeyPad(int pin):_pinAnalog(pin){
  //pinMode(_pinAnalog, INPUT_PULLUP);  // set pull-up on analog pin
  this->_prevKey = NO_KEY;
}

void KeyPad::Init(){}

//function for getting keypad value
int KeyPad::ambilNilai(){
      int keyVal = analogRead(_pinAnalog);
      return keyVal;
  }

//Convert keypad value to char with debouncing mechanism
char KeyPad::ambilCode(){
      int key = ambilNilai();
      char keyPad = NO_KEY;//Default key, No key
      char keyReturn = NO_KEY;//Default key, No key
      if (key < 60) {
        keyPad =  RIGHT;
      }
      else if (key < 200) {
        keyPad = UP;
      }
      else if (key < 400){
        keyPad = DOWN;
      }
      else if (key < 600){
        keyPad = LEFT;
      }
      else if (key < 800){
        keyPad = SELECT;
      }
      
      //debouncing mechanism
      if (this->_prevKey != keyPad){
        this->_prevMilli = millis();
        this->_prevKey = keyPad;
      }

      else {
        if ((millis() - this->_prevMilli) > DEBOUNCE_DELAY){
          this->_prevMilli = millis();
          this->_prevKey = keyPad;
          keyReturn = keyPad;
        }
      }
    return keyReturn;
  }  
