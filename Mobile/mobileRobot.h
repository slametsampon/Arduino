#ifndef mobileRobot_h
#define mobileRobot_h

#include "Arduino.h"
#include "command.h"
#include "dataModel.h"
#include "AnalogInput.h"
//#include "lcdTft.h"
#include <L298N.h>

#define   TURN_RATIO    10 //in percentage
#define   MAX_SPEED     0xFF //255
#define   MAX_GEAR      6 //Max Gear position
#define   MAX_TRACK     20 //Max tracking record
#define   MAX_IDL       25000 //Max Idle time milli second
#define   MILIS_RAND    1500 // lama gerakan random robot dalam milli detik

#define   MAX_SENSOR_GARIS      10 //Maximum Input command devices
#define   MAX_CAHAYA    100 //Maximum nilai cahaya 
#define   GELAP         80 //Batas gelap - terang
#define   ORT_KIRI      0 //Orientasi ukur jarak Kiri
#define   ORT_KANAN     180 //Orientasi ukur jarak Kanan
#define   ORT_LURUS     90 //Orientasi ukur jarak Lurus
#define   TRIGGER_PIN   47  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define   ECHO_PIN      48  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define   MAX_DISTANCE  200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define   JARAK_AMAN    20 // Maximum jarak aman cm 

typedef void (*CallBackFunction) ();
typedef struct sensData{
  float value;//value from sensor
  bool flFree;//
};
class mobileRobot{
  public:
    static unsigned char cmdInNbr;
    static unsigned char getCmdInNbr(){
      return cmdInNbr;
    }
    static unsigned char sensNbr;//It SHALL BE INITIALIZED FIRST IN *.ino file
    static unsigned char getSensNbr(){
      return sensNbr;
    }

    mobileRobot(String id):_id(id){}    
    void init();
    void attachCmdIn(command*);
    void attachMotor(L298N*, L298N*);
    void attachSensor(AnalogInput*);
    //void attachLcd(lcdTft*);
    void attachDiagTool(diagTool *tool){_diagTool = tool;}
    char getCommand();
    void setCommand(char);
    String action(char);
    bool isMoveable();
    void doFor(struct cmdRobot*);
    void doFor(struct cmdRobot*, CallBackFunction);
    void autoGaris();
    
  private:    
    String _id;
    char _prevCmd;
    String _cmdString;
    unsigned long  _prevMilli;
    sensData  _sensData[MAX_SENSOR_GARIS];
    unsigned short _normalSpeed, _turnSpeed;
    char _prevAction, _gearPost, _curCmd;//previous movement command
    bool _canMove;
    static void dummyCallback(){}
    diagTool  *_diagTool;
    //attachment devices
    L298N *_motKiri, *_motKanan;
    command *_cmdInput[MAX_CMD_INPUT];
    AnalogInput *_sensorGaris[MAX_SENSOR_GARIS];
    //lcdTft *_lcdTft;
    //private function
    void _reset();
    void _forward();
    void _backward();
    void _stop();
    void _turnLeft();
    void _turnRight();
    void _forwardLeft();
    void _forwardRight();
    void _backwardLeft();
    void _backwardRight();
    void _changeGear(char);
};
#endif
