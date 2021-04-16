
#include "mobileRobot.h"
#include "src\compDevices\motor.h"

Motor motorLeft(PIN_MOTOR_LEFT_ENA, PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2);
Motor motorRight(PIN_MOTOR_RIGHT_ENB, PIN_MOTOR_RIGHT_IN3, PIN_MOTOR_RIGHT_IN4);

MobileRobot mobileRobot("mobileRobot");


void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);


  motorLeft.init("motorLeft");
  motorRight.init("motorRight");

  mobileRobot.attachMotor(&motorLeft, &motorRight);

  mobileRobot.info();

  mobileRobot.move(CMD_FORWARD);

}

void loop() {


}
