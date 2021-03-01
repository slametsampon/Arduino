#include "Arduino.h"
#include "command.h"
#include "mobile.h"
#include "lcdTft.h"
#include "mobileRobot.h"
#include "controller.h"
#include "AnalogInput.h"

diagTool  DiagTool("DiagTool");
controller rbtMgr("Controller");

mobileRobot robot2W("2W Robot");
L298N motorKanan(PIN_SPEED_MOT_KANAN, PIN_MOT_KANAN1, PIN_MOT_KANAN2);
L298N motorKiri(PIN_SPEED_MOT_KIRI, PIN_MOT_KIRI1, PIN_MOT_KIRI2);
serialCmd _serInput("Serial Command");
bluetoothCmd _btInput("Bluetooth Command");
//lcdTft LcdTft("LCD Display");
AnalogInput sensGarisKiri(PIN_SENSOR_GARIS_KIRI);
AnalogInput sensGarisKanan(PIN_SENSOR_GARIS_KANAN);

//Static member class should be initialized FIRST (IF NOT ERROR)
unsigned char mobileRobot::cmdInNbr=0;
unsigned char mobileRobot::sensNbr=0;

void setup(){
    Serial.begin(9600);
    pinMode(PIN_LED_LIVE, OUTPUT);      // sets the digital pin as output

    initSensorGaris();

    //LcdTft.init();
    //LcdTft.buildComponent();
    
    robot2W.init();
    rbtMgr.init(&robot2W);
    rbtMgr.initSenamCsv();
    rbtMgr.initSenam();
    //attach DiagTool
    rbtMgr.attachDiagTool(&DiagTool);

    //attach serialCommands
    robot2W.attachCmdIn(&_serInput);
    robot2W.attachCmdIn(&_btInput);

    //attach LcdTft
    //robot2W.attachLcd(&LcdTft);

    //attach sensor garis
    robot2W.attachSensor(&sensGarisKiri);
    robot2W.attachSensor(&sensGarisKanan);
    
    //attach motors
    robot2W.attachMotor(&motorKiri, &motorKanan);

    //attach DiagTool
    robot2W.attachDiagTool(&DiagTool);

}

void loop(){
    liveLED();
    rbtMgr.action();
}

//functions declaration
void liveLED(){
  static unsigned long  _prevMilli;
  if ((millis() - _prevMilli) >= BLINK_TIME){
    _prevMilli = millis();
    digitalWrite( PIN_LED_LIVE, digitalRead(PIN_LED_LIVE) ^ 1 );
  }
}

void initSensorGaris(){
  sensGarisKiri.setAlfaEma(80);//in percentage
  sensGarisKiri.setRaw_Hi(1023);//10 bits
  sensGarisKiri.setRaw_Lo(0);
  sensGarisKiri.setPV_Hi(100);
  sensGarisKiri.setPV_Lo(0);
  sensGarisKiri.setCalcType(PV_AUTO);

  sensGarisKanan.setAlfaEma(80);//in percentage
  sensGarisKanan.setRaw_Hi(1023);//10 bits
  sensGarisKanan.setRaw_Lo(0);
  sensGarisKanan.setPV_Hi(100);
  sensGarisKanan.setPV_Lo(0);
  sensGarisKanan.setCalcType(PV_AUTO);

}
