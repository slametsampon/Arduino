#include <NewPing.h>
#include <Servo.h>

LcdTft tftLCD("LCD Display");
Servo arahJarak;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
L298N motorKanan(PIN_SPEED_MOT_KANAN, PIN_MOT_KANAN1, PIN_MOT_KANAN2);
L298N motorKiri(PIN_SPEED_MOT_KIRI, PIN_MOT_KIRI1, PIN_MOT_KIRI2);
sensorGaris garisKiri(PIN_SENSOR_GARIS_KIRI); 
sensorGaris garisKanan(PIN_SENSOR_GARIS_KANAN); 
sensorJarak jarak(&sonar);
kepala Kepala(&jarak, &arahJarak);

class robotMgr{
  public:
    robotMgr(robot2W *Robot):_Robot(Robot){
      _Robot->init();
      _Robot->action(BERHENTI);
    }

    void setupAcc(){
      _Robot->addMotors(&motorKiri, &motorKanan);    
      _Robot->addSensorGaris(&garisKiri, &garisKanan);    
      _Robot->addHead(&Kepala);    
    }
  
    void action(char cmdVal){
      char _cmd = cmdVal;
      _Robot->action(_cmd);
    }
  
    void actionFor(cmdRobot *cmdVal){
      if (!this->isMoveable()){      
        _cmdFor = *cmdVal;
        _Robot->reset();         
      }
      else _Robot->actionFor(_cmdFor);
    }

    String displayAction(){
      return _Robot->displayAction();
    }
  
    char getCurCmd(){
      return _Robot->getCurCmd();
    }
    bool isMoveable(){
      return _Robot->isMoveable();
    }
    
    bool autoGaris(){
      char prevCmd = _Robot->getCurCmd();//previous command
  
      _freeRobot = _Robot->getFree();// getFree
      
      if(_freeRobot.Kiri && _freeRobot.Kanan){
        if ((byte) random(0, 2))_Robot->action(MAJU_KIRI);
        else _Robot->action(MAJU_KANAN);
      }
      if(!_freeRobot.Kiri && _freeRobot.Kanan)_Robot->action(BELOK_KIRI);
      if(_freeRobot.Kiri && !_freeRobot.Kanan)_Robot->action(BELOK_KANAN);
      if(!_freeRobot.Kiri && !_freeRobot.Kanan){
        if (!_Robot->isMoveable()){
          if ((byte) random(0, 2))_Robot->action(MAJU_KIRI);
          else _Robot->action(MAJU_KANAN);
          _Robot->reset();         
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }    
  
    bool autoJarak(){
      char prevCmd = _Robot->getCurCmd();//previous command
      _freeRobot = _Robot->getFree();// getFree
  
      if(_freeRobot.JarakLurus)_Robot->action(MAJU);//lurus aman dari halangan
      else{
        if (_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action(BELOK_KIRI);   
        if (!_freeRobot.JarakKiri && _freeRobot.JarakKanan) _Robot->action(BELOK_KANAN);   
        if (!_freeRobot.JarakKiri && !_freeRobot.JarakKanan) _Robot->action(MUNDUR);   
        else {
          if (!_Robot->isMoveable()){
            _cmdFor.miliS = MILIS_RAND; 
            _cmdFor.cmd = (byte) random(0, 2);
            if ((byte) random(0, 2))_cmdFor.cmd = BELOK_KIRI;
            else _cmdFor.cmd = BELOK_KANAN;
            _Robot->reset();         
          }
          _Robot->actionFor(_cmdFor);
        }
      }
      if(prevCmd != _Robot->getCurCmd())return true;
      else return false;
    }
  
  private:
    String  _id;
    cmdRobot _cmdFor;
    sensorRobot _sensorRobot;
    freeRobot _freeRobot;
    robot2W *_Robot;
};
