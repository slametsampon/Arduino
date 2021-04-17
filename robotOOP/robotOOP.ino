
#include "mobileRobot.h"
#include "src\compDevices\motor.h"
#include "src\ioDevices\digitalOutput.h"

DigitalOutput ledLife(LED_BUILTIN);

Motor motorLeft(PIN_MOTOR_LEFT_ENA, PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2);
Motor motorRight(PIN_MOTOR_RIGHT_ENB, PIN_MOTOR_RIGHT_IN3, PIN_MOTOR_RIGHT_IN4);

MobileRobot mobileRobot("mobileRobot");

int gear = 0;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);


  motorLeft.init("motorLeft");
  motorRight.init("motorRight");

  mobileRobot.attachMotor(&motorLeft, &motorRight);

  mobileRobot.info();

  //mobileRobot.move(MOBILE_FORWARD);
  //mobileRobot.status();

}

void loop() {
  ledLife.blink(500);

  mobileRobot.move(MOBILE_FORWARD, gear, 5000, mobileCallback);
}

void mobileCallback(){
  gear += 1;

  if (gear > MAX_GEAR)gear=0;

  mobileRobot.reset();
}