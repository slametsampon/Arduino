
/*
  motor.h - Library untuk motor
  Dibuat Oleh : Sam April 15, 2021
*/

#include "motor.h"

Motor::Motor(int pinEa, int pin1, int pin2):
    _pinEnable(pinEa), _pinIN1(pin1), _pinIN2(pin2),_device("Motor"){

    this->init(_device);
}

void Motor::init(String id){
    _id = id;
    pinMode(_pinEnable, OUTPUT);
    pinMode(_pinIN1, OUTPUT);
    pinMode(_pinIN2, OUTPUT);
}

void Motor::info(){
  Serial.println("Motor::info()");

  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_device : ");
  Serial.println(_device);

  Serial.print("_pinEnable : ");
  Serial.println(_pinEnable);

  Serial.print("_pinIN1 : ");
  Serial.println(_pinIN1);

  Serial.print("_pinIN2 : ");
  Serial.println(_pinIN2);

  Serial.println(" ");

}

void Motor::status(){
  Serial.println("Motor::status()");
  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_cmdStr : ");
  Serial.println(_cmdStr);

  Serial.print("_pwmVal : ");
  Serial.println(_pwmVal);

  Serial.println(" ");

}

void Motor::move(char cmd){
    this->move(cmd, MAX_PWM);
}

void Motor::move(char cmd, int speed){

    _pwmVal = speed;
    _cmd = cmd;
    analogWrite(_pinEnable, _pwmVal);

    switch (_cmd)
    {
        case MOTOR_STOP:
            analogWrite(_pinEnable, MAX_PWM);
            this->_stop();
            _cmdStr = "MOTOR_STOP";
            break;
        
        case MOTOR_FORWARD:
            this->_forward();
            _cmdStr = "MOTOR_FORWARD";
            break;
        
        case MOTOR_BACKWARD:
            this->_backward();
            _cmdStr = "MOTOR_BACKWARD";
            break;
        
        default:
            break;
    }
}

void Motor::_forward(){
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, LOW);

}

void Motor::_backward(){
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, HIGH);

}

void Motor::_stop(){
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, LOW);
  
}

