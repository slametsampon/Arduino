#include "mobileRobot.h"

MobileRobot::MobileRobot(String id):_id(id), _device("MobileRobot"){

    //this->init(_device);
}

void MobileRobot::init(String id){
    _id = id;
}

void MobileRobot::move(int cmd){
    this->move(cmd,MAX_GEAR);
}

void MobileRobot::move(int cmd, int gear){
    switch (cmd)
    {
        case CMD_FORWARD:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            break;
        
        case CMD_BACKWARD:
            _motorLeft->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            break;
        
        case CMD_TURN_LEFT:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_STOP, this->_setSpeed(gear));
            break;
        
        case CMD_TURN_RIGHT:
            _motorLeft->move(MOTOR_STOP, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            break;
        
        case CMD_AROUND_LEFT:
            _motorLeft->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            break;
        
        case CMD_AROUND_RIGHT:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            break;
        
        case CMD_STOP:
            _motorLeft->move(MOTOR_STOP, this->_setSpeed(gear));
            _motorRight->move(MOTOR_STOP, this->_setSpeed(gear));
            break;
        
        default:
            break;
    }
}

void MobileRobot::info(){
  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_device : ");
  Serial.println(_device);

  Serial.println("Attachment : ");
  _motorLeft->info();
  _motorRight->info();

}

void MobileRobot::attachMotor(Motor *left, Motor *right){
    _motorLeft = left;
    _motorRight = right;
}

void MobileRobot::fakeCallback(){

}

int MobileRobot::_setSpeed(int gear){
    int speed = (gear*MAX_PWM)/MAX_GEAR;
    return speed;
}