#include <L298N.h>

typedef void (*CallBackFunction) ();
class robot2W
{
  public:
    void init(){
      _normalSpeed = MAX_SPEED*6/MAX_GEAR;
      _turnSpeed = _normalSpeed*TURN_RATIO/100;
      _motKiri->setSpeed(_normalSpeed);
      _motKanan->setSpeed(_normalSpeed);
      _gearPost = 6;
      _canMove = true;
      _Kepala->init(PIN_SERVO);
    }

    void addSensorGaris(sensorGaris *senKiri, sensorGaris *senKanan){
      _sensorGarisKiri = senKiri;
      _sensorGarisKanan = senKanan;
    }

    void addMotors(L298N *motKiri, L298N *motKanan){
      _motKiri = motKiri;
      _motKanan = motKanan;
    }

    void addHead(kepala *Kepala){
      _Kepala = Kepala;
    }
    
    char getCurCmd(){
      return _curCmd;
    }

    bool isMoveable(){
      return _canMove;
    }

    void reset(){
      _canMove = true;
    }

    String displayAction(){
      String strVal;
      strVal = ("Gear : ");
      strVal = (strVal + this->_gearPost);
      strVal = (strVal + "\n");
      strVal = (strVal + this->_curCmdStr);
      strVal = (strVal + "\nmilli S : ");
      strVal = (strVal + _cmdFor.miliS);
      return strVal;
    }

    void actionFor(cmdRobot cmdFor){
      this->actionFor(cmdFor,dummyCallback);
      _cmdFor.miliS = 0;
    }

    void actionFor(cmdRobot cmdFor, CallBackFunction callbackFor){
      _cmdFor = cmdFor;
      if ((_lastMs == 0)  && (_canMove)){
        this->action(_cmdFor.cmd);
        _lastMs = millis();
      }
      if (((millis() - _lastMs) > _cmdFor.miliS ) && (_canMove)){
        _canMove = false;
        _lastMs = 0;
        
        callbackFor();
      }      
    }
    
    void action(char incomingCmd) {
        if ((incomingCmd >= GEAR0) && (incomingCmd <= GEAR6)) this->pindahGigi(incomingCmd);
        if ((incomingCmd >= MAJU) && (incomingCmd <= BERHENTI)) this->Jalan(incomingCmd);
    }
    
    sensorRobot getSensor(){
      _sensorRobot.Kiri = _sensorGarisKiri->getValue();
      _sensorRobot.Kanan = _sensorGarisKanan->getValue();
      _sensorRobot.JarakKanan = _Kepala->tengokKanan();
      _sensorRobot.JarakLurus = _Kepala->tengokLurus();
      _sensorRobot.JarakKiri = _Kepala->tengokKiri();

      return _sensorRobot;
    }

    freeRobot getFree(){
      _freeRobot.Kiri = _sensorGarisKiri->isFree(GELAP);
      _freeRobot.Kanan = _sensorGarisKanan->isFree(GELAP);
      _freeRobot.JarakKanan = _Kepala->isTengokKananFree(JARAK_AMAN);
      _freeRobot.JarakLurus = _Kepala->isTengokLurusFree(JARAK_AMAN);
      _freeRobot.JarakKiri = _Kepala->isTengokKiriFree(JARAK_AMAN);

      return _freeRobot;
    }
    
  private:
    unsigned short _normalSpeed, _turnSpeed;
    char _prevMove, _gearPost, _curCmd;//previous movement command
    unsigned long _lastMs;
    unsigned long _prevSimMs;
    bool _canMove;
    String _curCmdStr;
    sensorRobot _sensorRobot;
    freeRobot _freeRobot;
    cmdRobot _cmdFor;
    L298N *_motKiri, *_motKanan;
    sensorGaris *_sensorGarisKiri, *_sensorGarisKanan;
    kepala *_Kepala;

    static void dummyCallback(){
      
    }
    void Jalan(char incomingCmd){
      switch (incomingCmd) {
        case BERHENTI:
          _curCmd = incomingCmd;
          _curCmdStr = "BERHENTI";
          _motKiri->stop();
          _motKanan->stop();
          _prevMove = incomingCmd;
          break;
        case MAJU:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MAJU_KANAN:
          _curCmdStr = "MAJU_KANAN";
          _curCmd = incomingCmd;
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MAJU_KIRI:
          _curCmd = incomingCmd;
          _curCmdStr = "MAJU_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->forward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR_KANAN:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KANAN";
          _motKiri->setSpeed(_normalSpeed);
          _motKanan->setSpeed(_turnSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case MUNDUR_KIRI:
          _curCmd = incomingCmd;
          _curCmdStr = "MUNDUR_KIRI";
          _motKiri->setSpeed(_turnSpeed);
          _motKanan->setSpeed(_normalSpeed);
          _motKiri->backward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case BELOK_KANAN:
          _curCmd = incomingCmd;
          _curCmdStr = "BELOK_KANAN";
          _motKiri->forward();
          _motKanan->backward();
          _prevMove = incomingCmd;
          break;
        case BELOK_KIRI:
          _curCmd = incomingCmd;
          _curCmdStr = "BELOK_KIRI";
          _motKiri->backward();
          _motKanan->forward();
          _prevMove = incomingCmd;
          break;
        default:
        break;
      }
  }   
  void pindahGigi(char gearVal){
    String inString = "";
    inString = (char)gearVal;
    _gearPost = inString.toInt();
    _normalSpeed = MAX_SPEED*_gearPost/MAX_GEAR;
    _turnSpeed = _normalSpeed*100/TURN_RATIO;
    this->action(_prevMove);// go to previous command
    if (_gearPost == 0)this->Jalan(BERHENTI); 
  }
};
