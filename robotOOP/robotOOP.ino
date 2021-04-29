
#include "src\ioDevices\digitalOutput.h"
#include "src\ioDevices\analogInput.h"
#include "src\compDevices\motor.h"
#include "src\serDevCmd\serDevCmd.h"
#include "mobileRobot.h"
#include "locPan.h"
#include "controller.h"
#include "commSer.h"

AnalogInput         keyAnalogIn(PIN_KEYPAD);
LiquidCrystal       lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad              keyPad(&keyAnalogIn);//declare keypad
serialCmd           serInput("serInput");
ViewLcd             view(lcd);//declare view, part of MVC pattern
AccessDataMenu      accessMenu("accessMenu");//part of MVC pattern
AccessParam         accessParam("accessParam");//part of MVC pattern
LocPan              locPan("locPan");//local panel

DigitalOutput ledLife(LED_BUILTIN);

DigitalOutput ledLeft(PIN_LED_LEFT);
DigitalOutput ledRight(PIN_LED_RIGHT);
LedLR ledLR(&ledLeft, &ledRight);
Motor motorLeft(PIN_MOTOR_LEFT_ENA, PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2);
Motor motorRight(PIN_MOTOR_RIGHT_ENB, PIN_MOTOR_RIGHT_IN3, PIN_MOTOR_RIGHT_IN4);
MobileRobot mobileRobot("mobileRobot");

AccessCmdRecord     accessGymRecord("accessGymRecord");
Controller  controller("controller");

//Variables declaration for commSer
CommSer     commSer("commSer");

AccessCommonData  accessCommonData("accessCommonData");//part of MVC pattern

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char       LocPan::cmdInNbr=0;
unsigned char       AccessDataMenu::menuNbr=0;

int gear = 0;
int operationMode;

//function declaration
void exceptionAct(int);

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  //attachment all peripherals for locPan
  locPan.attachCmdIn(&keyPad);
  locPan.attachCmdIn(&serInput);
  locPan.attachView(&view);
  locPan.attachModelMenu(&accessMenu);
  locPan.attachModelParameter(&accessParam);
  locPan.attachModelCommonData(&accessCommonData);
  //init for peripherals
  locPan.init();
  locPan.info();

  //attachment all peripherals for mobileRobot
  mobileRobot.attachMotor(&motorLeft, &motorRight);
  mobileRobot.attachLedLR(&ledLR);

  //attachment all peripheral for controller
  controller.attachMobileRobot(&mobileRobot);
  controller.attachGymRecord(&accessGymRecord);
  controller.attachModelCommonData(&accessCommonData);
  //init for peripherals
  controller.init();
  controller.info();

}

void loop() {
  ledLife.blink(500);

  operationMode = locPan.menu();
  controller.execute(operationMode);

  //get exception, and action as per exception code
  exceptionAct(locPan.getException());//get parameter exception
  exceptionAct(controller.getException());//get operation exception
  exceptionAct(commSer.getException());//get remote exception

}

void exceptionAct(int exp){
  switch (exp)  {
    case LOCAL_MODE_EXCEPTION:
      //commSer.sendValue();
      break;
    
    case LOCAL_PARAMETER_EXCEPTION:
      //controller.updateParameter();
      //locPan.updateParameter();
      //commSer.sendParameter();
      break;

    case REMOTE_MODE_EXCEPTION:
      //controller.execute();//1. check status controller (getValue, getMode)
      break;
    
    case REMOTE_PARAMETER_EXCEPTION:
      //controller.updateParameter();
      //locPan.updateParameter();
      //controller.execute();//1. check status controller (getValue, getMode)
      break;

    default:
      break;
  }
}
