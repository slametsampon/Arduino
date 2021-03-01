/*
  command.h - Library untuk command
  Dibuat Oleh : Sam May 2020
*/
#ifndef command_h
#define command_h

#define   MAJU              'A' //Robot Maju
#define   MUNDUR            'B' //Robot Mundur
#define   BELOK_KIRI        'C' //Robot Belok Kiri
#define   BELOK_KANAN       'D' //Robot Belok Kanan
#define   MAJU_KIRI         'E' //Robot Maju Serong Kiri
#define   MAJU_KANAN        'F' //Robot Maju Serong Kanan
#define   MUNDUR_KIRI       'G' //Robot Mundur Serong Kiri
#define   MUNDUR_KANAN      'H' //Robot Mundur Serong Kanan
#define   BERHENTI          'I' //Stop Bluetooth Command
#define   GEAR0             '0' //Gear position 0
#define   GEAR1             '1' //Gear position 1
#define   GEAR2             '2' //Gear position 2
#define   GEAR3             '3' //Gear position 3
#define   GEAR4             '4' //Gear position 4
#define   GEAR5             '5' //Gear position 5
#define   GEAR6             '6' //Gear position 6
#define   STOP_TRACK        'X' //Stop STOP_TRACK command
#define   STOP_RECORD       'X' //Stop STOP_RECORD command
#define   STOP_REMOTE       'X' //Stop STOP_REMOTE command
#define   STOP_AUTO         'X' //Stop STOP_AUTO command
#define   RESET             'Z' //Reset robot doFor

#define   MENU_UTAMA        'M' //Robot in Main menu 
#define   REMOTE            'L' //Robot Remote/Linnk by Remote Control
#define   SENAM             'S' //Robot Senam Mode
#define   RECORD            'R' //Robot Record Action
#define   TRACKING          'T' //Play on Tracking record
#define   AUTO_GARIS        'Q' //Play on Auto garis
#define   AUTO_JARAK        'J' //Play on Auto Jarak
#define   MAX_CMD_INPUT      4 //Maximum Input command devices
#define   STOP_BT           '%' //Stop Bluetooth Command
#define   INV_CMD           '%' //Stop Bluetooth Command
#define   BAUD_BT           57600 //Baud rate Bluetooth bps

#include "Arduino.h"

class command{
  public:    
    virtual char getCommand();
    bool isValid(char);
};

class serialCmd : public command{
  public:
    serialCmd(String);
    char getCommand();
  private:
    String  _id;    
    char  _cmd;    
};//end class

class bluetoothCmd : public command{
  public:
    bluetoothCmd(String);
    virtual char getCommand();
  private:
    char  _cmd;
    String  _id;    
};//end class

class diagTool{
  public:
    diagTool(String id):_id(id){}
    show (String label1, String label2, char val1, char val2){
      static unsigned long  _prevMilli;
      static char cnt;
      if ((millis() - _prevMilli) >= 1000){
        _prevMilli = millis();
        cnt++;
        if (cnt >= 5){
          cnt = 0;
          _label = " ";
          _label = label1 + " : ";
          Serial.print(_label);
          Serial.println(val1);

          _label = " ";
          _label = label2 + " : ";
          Serial.print(_label);
          Serial.println(val2);
        }
      }
    }
  private:
    String _label, _id;
};//end class

#endif
