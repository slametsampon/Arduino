/*
 * lihat header file RelayProt.h lebih detail
 * extention file harus .cpp bukan .CPP
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
*/

/* Dependencies */
#include "RelayProt.h"
#include "Arduino.h"

RelayProt::RelayProt(String id)
{
	_id = String(id);
	_active = false;
	_state = false;
	_actionChar = OVR_ACTION;
	_timeChar = DEF_TIME;
	_state = STATUS_OK;
}

String RelayProt::getId()
{
	return _id;
}

void RelayProt::setTimeDef(unsigned int val)
{
	_tDefSet = val;
}
void RelayProt::setPinTest(char pin)
{
	_pinTest = pin;
	pinMode(_pinTest, INPUT);
}
char RelayProt::getPinTest()
{
	return _pinTest;
}

void RelayProt::setPinReset(char pin)
{
	_pinReset = pin;
	pinMode(_pinReset, INPUT);
}
char RelayProt::getPinReset()
{
	return _pinReset;
}

void RelayProt::setPinLED(char pin)
{
	_pinLED = pin;
	pinMode(_pinLED, OUTPUT);
}
char RelayProt::getPinLED()
{
	return _pinLED;
}

void RelayProt::setPinRL(char pin)
{
	_pinRL = pin;
	pinMode(_pinRL, OUTPUT);
}
char RelayProt::getPinRL()
{
	return _pinRL;
}

void RelayProt::setValue(float val)
{
	_value = val;
}
float RelayProt::getValue()
{
	return _value;
}

void RelayProt::setTMS(unsigned int val)
{
	_tms = val;
}
unsigned int RelayProt::getTMS()
{
	return _tms;
}

void RelayProt::setSetting(float val)
{
	if (val > 0) _setting = val;
}
float RelayProt::getSetting()
{
	return _setting;
}

void RelayProt::setActive(boolean val)
{
	_active = val;
}
boolean RelayProt::isActive()
{
	return _active;
}

void RelayProt::setTimeChar(char val)
{
	_timeChar = val;
}
char RelayProt::getTimeChar()
{
	return _timeChar;
}

void RelayProt::setActionChar(byte val)
{
	_actionChar = val;
}
byte RelayProt::getActionChar()
{
	return _actionChar;
}

void RelayProt::setState(byte val)
{
	_state = _state | val;
}
byte RelayProt::getState()
{
  return _state;
}
unsigned int RelayProt::getTimeACC(){
	return _timeAcc;
}

unsigned int RelayProt::getTimeDef(){
	return _tDefSet;
}

void RelayProt::setReset(boolean val)
{
	_reset = val;
}

unsigned int RelayProt::calculateInverseTime(){
	unsigned int tempTime;
	float valTime;

  float ratio = _value/_setting;// ratio -> arus gangguan/setting
  
	switch (_timeChar){
	  case INVS_STD:
		valTime = (0.14/(pow(ratio,0.02) - 1.0))*(_tms/1000);//dalam detik
		break;
	  case INVS_VERY:
		valTime = (13.5/(pow(ratio,1.0) - 1.0))*(_tms/1000);//dalam detik
		break;
	  case INVS_EXTREM:
		valTime = (80.0/(pow(ratio,2.0) - 1.0))*(_tms/1000);//dalam detik
		break;
	  case INVS_LONG:
		valTime = (120.0/(pow(ratio,1.0) - 1.0))*(_tms/1000);//dalam detik
		break;
	  break;
	  default:
	  break;
	}

  
  tempTime = (unsigned int) valTime * 1000.0;//dalam milli detik
  if (tempTime > MAX_MILLI) tempTime = (unsigned int) MAX_MILLI;//set to maksimum 65535
  return tempTime;  
}

unsigned int RelayProt::countDownTime(){
  unsigned int deltaMilli;

  // mekanisme roll over Milli()
  if (_currMilli < _prevMilli){
	deltaMilli = MAX_MILLI - _prevMilli;
	deltaMilli = deltaMilli + _currMilli;
  }
  else deltaMilli = _currMilli - _prevMilli;
  //-------------------
  
   if (_timeAcc < deltaMilli) _timeAcc = 0;//milli detik
   else _timeAcc = _timeAcc - deltaMilli;//milli detik
  _prevMilli = _currMilli;
  return _timeAcc;
}

void RelayProt::execute(float val)
{
	unsigned int tempTime;
	_currMilli = millis();
	_value = val;
	
	if (_active){
		if (digitalRead(_pinReset)) _reset = true;
		if (_reset){
			_reset = false;
			if (_state >= STATUS_TRIP){
				digitalWrite( _pinLED, false );
				digitalWrite( _pinRL, false );
				_timeAcc = (unsigned int) MAX_MILLI;//65535 milli detik
				_state = STATUS_OK;
			}
			return;
		}

		if (_state >= STATUS_TRIP)return;//no logic if trip......
		
		//baca input PIN
		if (digitalRead(_pinTest))_state = STATUS_TEST_LOCAL;//Pin test Arduino active

		switch (_state){
		  case STATUS_TEST_LOCAL:
			goto CHECK_STATUS;// Trip karena PIN local Arduino aktif dan Instant
		  break;
		  case STATUS_TEST_KEY:
			goto CHECK_STATUS;// Trip karena Keypad local Arduino aktif dan Instant
		  break;
		  case STATUS_TEST_REMOTE:
			goto CHECK_STATUS;// Trip karena remote/host aktif dan Instant
		  break;
		  default:
		  break;
		}

		//check action characeristik
		switch (_actionChar){
		  case OVR_ACTION:
			if (_value > _setting){
				if (!_startCountDown)_prevMilli = _currMilli;
				_startCountDown = true;
				_state = _state | STATUS_OVER;
				}
			if (_value <= _setting){
				_startCountDown = false;
				_state = STATUS_OK;
				}
		  break;
		  case UDR_ACTION:
			if (_value < _setting){
				if (!_startCountDown)_prevMilli = _currMilli;
				_startCountDown = true;
				_state = _state | STATUS_UNDER;
				}
			if (_value >= _setting){
				_startCountDown = false;
				_state = STATUS_OK;
				}
		  break;
		  case EQL_ACTION:
			if (_value == _setting){
				if (!_startCountDown)_prevMilli = _currMilli;
				_startCountDown = true;
				_state = _state | STATUS_EQUAL;
				}
			if (_value != _setting){
				_startCountDown = false;
				_state = STATUS_OK;
				}
		  break;
		  default:
		  break;
		}
		//check time characeristik
		switch (_timeChar){
		  case INST_TIME:
			if (!_startCountDown) _timeAcc = 0;
		  break;
		  case DEF_TIME:
			if (!_startCountDown) _timeAcc = _tDefSet;
		  break;
		  case INVS_STD:
		  case INVS_VERY:
		  case INVS_EXTREM:
		  case INVS_LONG:
			if (!_startCountDown)_timeAcc = (unsigned int) MAX_MILLI;//saat pertama kali hitung mundur
			else {
				tempTime = calculateInverseTime();
			  if (_timeAcc >= tempTime)_timeAcc = tempTime;
			}
		  break;
		  default:
		  break;
		}

		//start counting down
		if (_startCountDown)_timeAcc = countDownTime();

		//check status Relay
CHECK_STATUS:
		switch (_state){
		  case STATUS_OVER:
			if (_timeAcc <= 0) _state = _state | STATUS_TRIP;// Trip karena sensor dan terjadi over
		  break;
		  case STATUS_UNDER:
			if (_timeAcc <= 0) _state = _state | STATUS_TRIP;// Trip karena sensor dan terjadi under
		  break;
		  case EQL_ACTION:
			if (_timeAcc <= 0) _state = _state | STATUS_TRIP;// Trip karena sensor dan terjadi under
		  break;
		  case STATUS_TEST_LOCAL:
			_state = _state | STATUS_TRIP;// Trip karena PIN local Arduino aktif dan Instant
		  break;
		  case STATUS_TEST_KEY:
			_state = _state | STATUS_TRIP;// Trip karena Keypad local Arduino aktif dan Instant
		  break;
		  case STATUS_TEST_REMOTE:
			_state = _state | STATUS_TRIP;// Trip karena remote/host aktif dan Instant
		  break;
		  default:
		  break;
		}
		
		//kirim Output
		if (_state >= STATUS_TRIP){
			digitalWrite( _pinLED, true );
			digitalWrite( _pinRL, true );
		}

	}
}
