#include "mobileRobot.h"
MobileRobot::MobileRobot(String id):_id(id), _device("MobileRobot"){

    _prevMs = 0;
    _isMoveable = true;
}

void MobileRobot::attachMotor(Motor *left, Motor *right){
    _motorLeft = left;
    _motorRight = right;
}

void MobileRobot::attachLedLR(LedLR *ledLR){
    _ledLR = ledLR;
}

void MobileRobot::init(){
    _motorLeft->init("_motorLeft");
    _motorRight->init("_motorRight");
    _ledLR->init();
}

void MobileRobot::init(String id){
    _id = id;
    this->init();
}

void MobileRobot::move(char cmd){
    this->move(cmd,MAX_GEAR);
}

void MobileRobot::move(char cmd, int gear){
    _cmd = cmd;
    _gear = gear;
    switch (_cmd)
    {
        case MOBILE_FORWARD:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _cmdStr = "MOBILE_FORWARD";
            break;
        
        case MOBILE_BACKWARD:
            _motorLeft->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _cmdStr = "MOBILE_BACKWARD";
            break;
        
        case MOBILE_TURN_LEFT:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_STOP, this->_setSpeed(gear));
            _cmdStr = "MOBILE_TURN_LEFT";
            break;
        
        case MOBILE_TURN_RIGHT:
            _motorLeft->move(MOTOR_STOP, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _cmdStr = "MOBILE_TURN_RIGHT";
            break;
        
        case MOBILE_AROUND_LEFT:
            _motorLeft->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _cmdStr = "MOBILE_AROUND_LEFT";
            break;
        
        case MOBILE_AROUND_RIGHT:
            _motorLeft->move(MOTOR_FORWARD, this->_setSpeed(gear));
            _motorRight->move(MOTOR_BACKWARD, this->_setSpeed(gear));
            _cmdStr = "MOBILE_AROUND_RIGHT";
            break;
        
        case MOBILE_STOP:
            _motorLeft->move(MOTOR_STOP, this->_setSpeed(gear));
            _motorRight->move(MOTOR_STOP, this->_setSpeed(gear));
            _cmdStr = "MOBILE_STOP";
            break;
        
        default:
            break;
    }
    _ledLR->status(_motorLeft->getCmd(), _motorRight->getCmd());
}

void MobileRobot::move(char cmd, int gear, unsigned long delay){
    this->move(cmd, gear, delay, fakeCallback);
}

void MobileRobot::move(char cmd, int gear, unsigned long delay, CallBackFunction callback){

    if ((_prevMs == 0) && _isMoveable){

        _prevMs = millis();
        this->move(cmd,gear);

    }

    if (((millis() - _prevMs) > delay) && _isMoveable){
        //this->status();
        this->move(MOBILE_STOP);
        _prevMs = 0;
        _isMoveable = false;

        callback();
    }
}

void MobileRobot::status(){
  Serial.println("MobileRobot::status()");

  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_cmdStr : ");
  Serial.println(_cmdStr);

  Serial.print("_gear : ");
  Serial.println(_gear);

  Serial.println("Attachment : ");
  _motorLeft->status();
  _motorRight->status();

}

void MobileRobot::info(){
  Serial.println("MobileRobot::info()");

  Serial.print("_id : ");
  Serial.println(_id);

  Serial.print("_device : ");
  Serial.println(_device);

  Serial.println("Attachment : ");
  _motorLeft->info();
  _motorRight->info();
  _ledLR->info();

}

void MobileRobot::fakeCallback(){

}

void MobileRobot::reset(){
    _isMoveable = true;
}

int MobileRobot::_setSpeed(int gear){
    int speed = (gear*MAX_PWM)/MAX_GEAR;
    return speed;
}
