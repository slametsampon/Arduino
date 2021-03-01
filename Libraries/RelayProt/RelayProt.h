/*
	ver 0.1 : 1. penambahan _currMilli, menggantikan millis() agar lebih bebas,
			  2. Penambahan   // mekanisme roll over Millis()
	  case INVS_STD:
		tempTime = (0.14/(pow(ratio,0.02) - 1.0))*_tms;//dalam detik
		break;
	  case INVS_VERY:
		tempTime = (13.5/(pow(ratio,1.0) - 1.0))*_tms;//dalam detik
		break;
	  case INVS_EXTREM:
		tempTime = (80.0/(pow(ratio,2.0) - 1.0))*_tms;//dalam detik
		break;
	  case INVS_LONG:
		tempTime = (120.0/(pow(ratio,1.0) - 1.0))*_tms;//dalam detik

 	ver 0.2 : 1. Perubahan konversi type data time dari unsigned long ke unsigned int.
				 Perubahan ini agar sesuai dengan data dari Modbus-unsigned int.
			  2. Penambahan conversi dari unsigned long ke unsigned int, untuk menghilangkan warning saat kompilasi
			  3. Menghilangkan konstanta AN_HOUR

  RelayProt.h - Library untuk Proteksi Relay
  Dibuat Oleh : Abi May 2017
*/
#ifndef RelayProt_h
#define RelayProt_h

#include "Arduino.h"

#define INST_TIME	1	//Instantaneous
#define DEF_TIME	2	//Definitive Time
#define INVS_STD	3	//Inverse Standard Time
#define INVS_VERY	4	//Inverse Very Time
#define INVS_EXTREM	5	//Inverse Extreme Time
#define INVS_LONG	6	//Inverse Long Time
#define OVR_ACTION	1	//Action when over than setting
#define UDR_ACTION	2	//Action when under than setting
#define EQL_ACTION	3	//Action when equel setting
#define MAX_MILLI 0xFFFFFFFF  //unsigned long 32 bits (4 bytes)
//status 
#define STATUS_OK  0 //Status OK
#define STATUS_TEST_LOCAL  1 //PIN LOCAL TEST AKTIF
#define STATUS_TEST_REMOTE  2 //REMOTE TEST AKTIF
#define STATUS_TEST_KEY  4 //KEY-PAD TEST AKTIF
#define STATUS_OVER  8 //_value over than _setting
#define STATUS_UNDER  16 //_value UNDER than _setting
#define STATUS_EQUAL  32 //_value EQUAL than _setting
#define STATUS_TRIP  64 //RL Trip

class RelayProt
{
  public:
    RelayProt(String id);
    void setPinTest(char pin);
    void setPinReset(char pin);
    void setPinLED(char pin);
    void setPinRL(char pin);
    void setValue(float val);
    void setTMS(unsigned int val);
    void setSetting(float val);
    void setTimeChar(char val);
    void setTimeDef(unsigned int val);
    void setActive(boolean val);
    void setActionChar(byte val);
    void setState(byte val);
    void setReset(boolean val);
    byte getState();
    String getId();
    char getPinTest();
    char getPinReset();
    char getPinLED();
    char getPinRL();
    float getValue();
    unsigned int getTMS();
    float getSetting();
    char getTimeChar();
	unsigned int getTimeACC();
    unsigned int getTimeDef();
    byte getActionChar();
    boolean isActive();
	void execute(float val);
  private:
    String _id;
    String _unit;
    char _pinTest;
    char _pinReset;
    char _pinLED;
    char _pinRL;
  	boolean _active,_flagReset,_startCountDown;
  	byte _state,_actionChar;
  	boolean _reset;
  	boolean _PrevReset;
  	float _value;
  	float _setting;
	unsigned long _prevMilli,_currMilli;
	unsigned int _tDefSet,_tms,_timeAcc;
  	char _timeChar;
  	//char _actionChar;
	unsigned int calculateInverseTime();
	unsigned int countDownTime();
};

#endif
