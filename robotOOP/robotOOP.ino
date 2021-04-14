
#include "mobileRobot.h"

L298N   motorLeft(PIN_L298N_LEFT_ENA, PIN_L298N_LEFT_IN1, PIN_L298N_LEFT_IN2);
L298N   motorRight(PIN_L298N_RIGHT_ENB, PIN_L298N_RIGHT_IN3, PIN_L298N_RIGHT_IN4);

//initial speed
unsigned short theSpeed = 0;

void setup() {

  //set the initial speed
  motorLeft.setSpeed(theSpeed);
  motorRight.setSpeed(theSpeed);

}

void loop() {

  //move motor for 5 seconds and then execute the callback function
  motorLeft.forwardFor(5000, callback);
  motorRight.forwardFor(5000, callback);

}

void callback() {

  //each time the callback function is called increase the speed of the motor or reset to 0
  if (theSpeed <= 255) {
    theSpeed += 25;
  } else {
    theSpeed = 0;
  }

  //re-enable motor movements
  motorLeft.reset();
  motorRight.reset();
  //set the new speed
  motorLeft.setSpeed(theSpeed);
  motorRight.setSpeed(theSpeed);

}
