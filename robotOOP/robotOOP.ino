
#include "src\ioDevices\digitalOutput.h"
#include "src\ioDevices\analogInput.h"
#include "src\compDevices\motor.h"
#include "src\serDevCmd\serDevCmd.h"
#include "mobileRobot.h"
#include "locPan.h"

AnalogInput         keyAnalogIn(PIN_KEYPAD);
LiquidCrystal       lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad              keyPad(&keyAnalogIn);//declare keypad
serialCmd           serInput("Serial Command");
ViewLcd             view(lcd);//declare view, part of MVC pattern
AccessDataMenu      accessMenu("Data Menu");//part of MVC pattern
LocPan              locPan("LocPan-Local Panel");//local panel


DigitalOutput ledLife(LED_BUILTIN);

DigitalOutput ledLeft(PIN_LED_LEFT);
DigitalOutput ledRight(PIN_LED_RIGHT);
LedLR ledLR(&ledLeft, &ledRight);
Motor motorLeft(PIN_MOTOR_LEFT_ENA, PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2);
Motor motorRight(PIN_MOTOR_RIGHT_ENB, PIN_MOTOR_RIGHT_IN3, PIN_MOTOR_RIGHT_IN4);

MobileRobot mobileRobot("mobileRobot");

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char       LocPan::cmdInNbr=0;
unsigned char       AccessDataMenu::menuNbr=0;

int gear = 0;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  //attachment all peripherals for locPan
  locPan.attachCmdIn(&keyPad);
  locPan.attachCmdIn(&serInput);
  locPan.attachView(&view);
  locPan.attachModelMenu(&accessMenu);
  //init for peripherals
  locPan.init();
  locPan.info();

  //attachment all peripherals for mobileRobot
  mobileRobot.attachMotor(&motorLeft, &motorRight);
  mobileRobot.attachLedLR(&ledLR);
  //init for peripherals
  mobileRobot.init();
  mobileRobot.info();

}

void loop() {
  ledLife.blink(500);

  mobileRobot.move(MOBILE_BACKWARD, gear, 5000, mobileCallback);
  locPan.menu();
}

void mobileCallback(){
  gear += 1;

  if (gear > MAX_GEAR)gear=0;

  mobileRobot.reset();
}