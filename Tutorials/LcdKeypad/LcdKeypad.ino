/*
Arduino 2x16 LCD - test program
modified on 07 Feb 2021
Testing : 
  Code/Setting/No INPUT_PULLUP/INPUT_PULLUP
  R/60/0/13
  U/200/131/125
  D/400/305/328
  L/600/479/502
  S/800/722/738
  No_Key/1023/1023
*/

#include <LiquidCrystal.h>//for LCD

// LCD pin setting
// For LCD Keypad DF Robot
#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define PIN_KEYPAD A0 // pin Analog Keypad
#define LCD_ROWS 2
#define LCD_COLUMNS 16
//pin no. 10 sementara tidak digunakan
// LCD
LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
unsigned long prevMilli;
int prevKey;
String prevKeyPad;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  pinMode(PIN_KEYPAD, INPUT_PULLUP);
  lcd.setCursor(0,0);
  lcd.print("LCD Keyboard Test");
  lcd.setCursor(0,1);
  lcd.print("By : sam");
  delay (2000);//delay 2 second
  lcd.clear();
}

//function for getting keypad value
int keypadGetKeyValue(unsigned long debouncingTime){
  int key = analogRead(PIN_KEYPAD);
  if (key != prevKey)prevMilli = millis();
  else{
    if ((millis() - prevMilli) > debouncingTime){
      prevMilli = millis();
      prevKey = key;
    }
  }
  return key;
}

//Convert keypad value to String
String keypadGetKeyPad(int key){
  String keyPad = "N";//Default key, No key
  if (key < 60) {
    keyPad =  ("R");//Right key
  }
  else if (key < 200) {
    keyPad =  ("U");//Up key
  }
  else if (key < 400){
    keyPad =  ("D");//Down key
  }
  else if (key < 600){
    keyPad =  ("L");//Left key
  }
  else if (key < 800){
    keyPad =  ("S");//Select key
  }
  return keyPad;
}

void loop() {
  // put your main code here, to run repeatedly:
  int prevVal;
  int key = keypadGetKeyValue(150);
  //float kf = key/3.4;
  String keyPad = keypadGetKeyPad(key);
  if (prevKeyPad != keyPad){
    prevKeyPad = keyPad;
    lcd.clear();

    //display key
    lcd.setCursor(0,0);
    lcd.print("Key : ");

    //display keypad
    lcd.setCursor(5,0);
    lcd.print(key, DEC);

    //display keypad
    lcd.setCursor(0,1);
    lcd.print("Keypad: ");

    //display keypad
    lcd.setCursor(7,1);
    lcd.print(keyPad);
  }

}
