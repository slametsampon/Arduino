/*
Arduino 2x16 LCD - test program
modified on 13 Feb 2021, for OOP
*/

#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

#include "LcdKeypad.h"//lihat file LcdKeypad.h

//Library yang dibuat sendiri lihat file KeyPad.h dan KeyPad.cpp
#include "KeyPad.h"
#include "SequenceTimer.h"
#include "Model.h"//part of MVC pattern, see Model.h
#include "View.h"//part of MVC pattern, see View.h
#include "Controller.h"//part of MVC pattern, see Controller.h


RTC_Millis rtc;//software RTC

//OOP - project
LiquidCrystal   lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad          keyPad(PIN_KEYPAD);//declare keypad
serialCmd       serInput("Serial Command");
View            view(lcd);//declare view, part of MVC pattern
SequenceTimer   sequenceUtama("Sequence");
AccessDataMenu  accessMenuUtama("Data Menu");//part of MVC pattern
AccessParameter accessParameter("Parameter");//part of MVC pattern
Controller      controller("Controller");//part of MVC pattern

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char Controller::cmdInNbr=0;
unsigned char AccessDataMenu::menuNbr=0;
unsigned char AccessParameter::paramNbr=0;

DateTime waktuSekarang;//mencatat waktu sekarang
String waktu;

//function

void setupParameter(){
  parameter param;
  Serial.println("LcdKeypadOOP-setupParameter");

  //fire Zone1.
  param.id = "Smoke-1";
  param.unit = "%";
  param.indexMenu = 1;
  param.value = 31;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  accessParameter.add(param);

  //fire Zone2.
  param.id = "Smoke-2";
  param.unit = "%";
  param.indexMenu = 2;
  param.value = 82;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  accessParameter.add(param);

  //fire Zone3.
  param.id = "Smoke-3";
  param.unit = "%";
  param.indexMenu = 3;
  param.value = 53;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  accessParameter.add(param);

  //fire Zone4.
  param.id = "Smoke-4";
  param.unit = "%";
  param.indexMenu = 4;
  param.value = 84;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  accessParameter.add(param);

  //fire Zone5.
  param.id = "Smoke-5";
  param.unit = "%";
  param.indexMenu = 5;
  param.value = 85;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  accessParameter.add(param);
}

void setupMenuUtama(){
  dataMenu  dtMenu;

  Serial.println("LcdKeypadOOP-setupMenuUtama");

  dtMenu.hasParameter = false;
  dtMenu.pesan1 ="Fire Protection System";
  dtMenu.pesan2 ="Salman Alfarisi";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 1";
  dtMenu.pesan2 ="Parameter 1";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 2";
  dtMenu.pesan2 ="Parameter 2";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 3";
  dtMenu.pesan2 ="Parameter 3";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 4";
  dtMenu.pesan2 ="Parameter 4";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 5";
  dtMenu.pesan2 ="Parameter 5";
  accessMenuUtama.add(dtMenu);

}
