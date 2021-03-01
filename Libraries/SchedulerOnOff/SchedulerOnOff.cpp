/*
 * lihat header file signalGenerator.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "SchedulerOnOff.h"
#include "Arduino.h"

// Constructor - creates a Flasher 
// and initializes the member variables and state
SchedulerOnOff::SchedulerOnOff(byte val){
  _modeType = val;
  _runCycle = DEFAULT_RUN_CYCLE;// mili detik 
}

unsigned long SchedulerOnOff::calculateMilliSecond(unsigned long valS,unsigned long valM,unsigned long valH){
  unsigned long val;
  val = valS + valM * 60;//dalam milli second
  val = val + valH * 60 * 60;//dalam milli second
  return val*1000;
}

boolean SchedulerOnOff::isFlRun(){
  unsigned long deltaMilli;

  // mekanisme roll over Milli()
  if (_currMilli < _prevMilli){
	deltaMilli = MAX_MILLI - _prevMilli;
	deltaMilli = deltaMilli + _currMilli;
  }
  else deltaMilli = _currMilli - _prevMilli;
  //-------------------
  
  if (deltaMilli >= _runCycle){
	_prevMilli = _currMilli;
	_flRun = true;
  }
return _flRun;
}

void SchedulerOnOff::setActive(boolean val){
  _active = val;  
  _1stRun = val;
  _currMilli = millis();
  if (_active){

  _prevMilli = _currMilli;
  _prevExeMilli = _prevMilli;
  _startCycle = _prevMilli;

  _periodeTime = calculateMilliSecond(_periodeSecond,_periodeMinute,_periodeHour);
  _initialStartTime = calculateMilliSecond(_initialStartSecond,_initialStartMinute,_initialStartHour);
  _durationOn = calculateMilliSecond(_durationOnSecond,_durationOnMinute,_durationOnHour);
	
	_TimeAccOn = _durationOn;
	if (_modeType == ONESHOOT_TYPE) _TimeAccOff = _initialStartTime;
	else _TimeAccOff = _periodeTime - _TimeAccOn;
  }
}
byte SchedulerOnOff::isActive(){
  return _active;  
}

boolean SchedulerOnOff::execute(){
	unsigned long deltaMilli;
	_currMilli = millis();

  if (_active && isFlRun()){
	_flRun = false;

	// mekanisme roll over Milli()
	if (_currMilli < _prevExeMilli){
	  deltaMilli = MAX_MILLI - _prevExeMilli;
	  deltaMilli = deltaMilli + _currMilli;
	}
	else deltaMilli = _currMilli - _prevExeMilli;
	_prevExeMilli = _currMilli;
	//-------------------

	if (!_status){
	  if (_TimeAccOff <= deltaMilli) _TimeAccOff = 0;
	  else _TimeAccOff = _TimeAccOff - deltaMilli;
	}
	if (_TimeAccOff <= 0) _status = true;

	if (_status){
	  if (_TimeAccOn <= deltaMilli) _TimeAccOn = 0;
	  else _TimeAccOn = _TimeAccOn - deltaMilli;
	}
	if (_TimeAccOn <= 0){
	  _status = false;
	 _1stRun = false;

	 //-----------------
	_periodeTime = calculateMilliSecond(_periodeSecond,_periodeMinute,_periodeHour);
	_initialStartTime = calculateMilliSecond(_initialStartSecond,_initialStartMinute,_initialStartHour);
	_durationOn = calculateMilliSecond(_durationOnSecond,_durationOnMinute,_durationOnHour);

	_TimeAccOn = _durationOn;
	_TimeAccOff = _periodeTime - _TimeAccOn;

	 _startCycle = _currMilli;//start new cycle for Cyclic Mode
	 if (_modeType == ONESHOOT_TYPE) _active = false;//sekali jalan saja, dan harus di-active-kan kembali jika akan jalan 
	}
  }
return  _status; 
}

void SchedulerOnOff::setRunCycle(unsigned int val){
  _runCycle = val;  
}
unsigned int SchedulerOnOff::getRunCycle(){
  return _runCycle;  
}

void SchedulerOnOff::setPeriodeHour(unsigned long val){
  _periodeHour = val;  
}
void SchedulerOnOff::setPeriodeMinute(unsigned long val){
  _periodeMinute = val;  
}
void SchedulerOnOff::setPeriodeSecond(unsigned long val){
  _periodeSecond = val;  
}
unsigned long SchedulerOnOff::getPeriodeTime(){
  return _periodeTime;  
}

void SchedulerOnOff::setInitialStartHour(unsigned long val){
  _initialStartHour = val;  
}
void SchedulerOnOff::setInitialStartMinute(unsigned long val){
  _initialStartMinute = val;  
}
void SchedulerOnOff::setInitialStartSecond(unsigned long val){
  _initialStartSecond = val;  
}
unsigned long SchedulerOnOff::getInitialStartTime(){
  return _initialStartTime;  
}

void SchedulerOnOff::setDurationOnHour(unsigned long val){
  _durationOnHour = val;  
}
void SchedulerOnOff::setDurationOnMinute(unsigned long val){
  _durationOnMinute = val;  
}
void SchedulerOnOff::setDurationOnSecond(unsigned long val){
  _durationOnSecond = val;  
}
unsigned long SchedulerOnOff::getDurationOn(){
  return _durationOn;  
}
