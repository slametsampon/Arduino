/*
 * lihat header file EventTimer.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "eventTimer.h"
#include "Arduino.h"

EventTimer::EventTimer(String id):_id(id){
	this->init();
}

void EventTimer::init(){
	_isEnable = true;
	_prevDelayMilli = millis();
	_isInputAvailable = true;
	_isOutputAvailable = true;
	_isCyclic = false;
	_isOneShoot = false;
	_prevStatus = false;

	_delayMilli = 0;
	_durationMilli = 0;

  _digInput->init(REVERSE_TYPE,"_digInput");
  _digOutput->init(FORWARD_TYPE,"_digOutput");
}

void EventTimer::init(boolean typ){
	_isEnable = true;
	_isInputAvailable = true;
	_isOutputAvailable = true;

  _digInput->init(typ,"_digInput");
  _digOutput->init(FORWARD_TYPE,"_digOutput");
}

void EventTimer::info(){
    Serial.println("EventTimer::info()");
    
	Serial.print("_isCyclic : ");
	Serial.println(_isCyclic);

	Serial.print("_isOneShoot : ");
	Serial.println(_isOneShoot);
  	Serial.println("");

    if (_isInputAvailable) _digInput->info();
    if (_isOutputAvailable)_digOutput->info();

	Serial.print("Delay Setting (H:M:S) : ");
	Serial.print(_delayHour);
	Serial.print(_delayMinute);
	Serial.println(_delaySecond);
	Serial.print("Delay Setting (milli) : ");
	Serial.println(_delayMilli);

	Serial.print("Duration Setting (H:M:S) : ");
	Serial.print(_durationHour);
	Serial.print(_durationMinute);
	Serial.println(_durationSecond);
	Serial.print("Duration Setting (milli) : ");
	Serial.println(_durationMilli);
}

void EventTimer::attachInput(DigitalInput *digInput){
	_digInput = digInput;
	_isInputAvailable = true;
}

void EventTimer::attachOutput(DigitalOutput *digOutput){
	_digOutput = digOutput;
	_isOutputAvailable = true;
}

void EventTimer::setEnable(boolean enable){
	_isEnable = enable;
	if (_isEnable)_prevDelayMilli = millis();
	else _prevDelayMilli = 0;
}

void EventTimer::setOneShoot(boolean oneShoot){
	_isOneShoot = oneShoot;
}

void EventTimer::setCyclic(boolean cyclic){
	_isCyclic = cyclic;
}

//set delay
void EventTimer::setDelay(unsigned long delayMilli){
	_delayMilli = delayMilli;
}

void EventTimer::setDelay(int minute, int second){
	_delaySecond = second;
	_delayMinute = minute;
	_delayMilli = (_delayMinute * A_MINUTE) + (_delaySecond * A_SECOND);
}

void EventTimer::setDelay(int hour, int minute, int second){
	_delayHour = hour;
	this->setDelay(minute, second);
}

//set duration
void EventTimer::setDuration(unsigned long durationMilli){
	_durationMilli = durationMilli;
}

void EventTimer::setDuration(int minute, int second){
	_durationSecond = second;
	_durationMinute = minute;
	_durationMilli = (_durationMinute * A_MINUTE) + (_durationSecond * A_SECOND);
}

void EventTimer::setDuration(int hour, int minute, int second){
	_durationHour = hour;
	this->setDuration(minute, second);
}

boolean EventTimer::execute(){
	boolean status = false;

	if (_isInputAvailable){
		_isEnable = _digInput->isStatus(150);//de-bouncing for milli second
		if (!_isEnable)_prevDelayMilli = 0;
		else _prevDelayMilli = millis();
	}

	if(!_isEnable) {
		if (_isOutputAvailable)this->_setOutput(status);
		return status;
	}

	//logic
	if ((millis() - _prevDelayMilli) > _delayMilli){
		status = true;
		if (_isOneShoot){
			if (!_prevStatus)_prevStatus = true;
			else{
				_prevStatus = false;
				status = false;
			}
		}
		
		//has duration
		if (_durationMilli <= 0){
			if(_prevDurationMilli == 0)_prevDurationMilli = millis();
			if((millis() - _prevDurationMilli) <= _durationMilli)status = true;
			else{
				_isEnable = false;
				_prevDelayMilli = 0;
			}
		}

		//cyclic
		if (_isCyclic){
			_isEnable = true;
			_prevDelayMilli = millis();
		}
	}

	if (_isOutputAvailable)this->_setOutput(status);

	return status;
}

void EventTimer::_setOutput(boolean status){
	if (status)_digOutput->on();
	else _digOutput->off();
}