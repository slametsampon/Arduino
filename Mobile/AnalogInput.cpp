/*
 * lihat header file AnalogInput.h lebih detail
 * extention file harus .cpp bukan .CPP
 * April 04, 2020 : Add Ema filter for Raw input
 */

/* Dependencies */
#include "AnalogInput.h"

AnalogInput::AnalogInput(char pin):_pin(pin){}

void AnalogInput::Init(){}

void AnalogInput::setUnit(String id)
{
	_unit = id;
}
String AnalogInput::getUnit()
{
	return _unit;
}

char AnalogInput::getPin()
{
	return _pin;
}

void AnalogInput::setPVSim(float val)
{
	_PVSim = val;
}
float AnalogInput::getPV()
{
	unsigned long tempVal;
	if (_CalcType == PV_AUTO){
		//calculate for EMA filter
		tempVal = (analogRead(_pin)*_alfaEma + (100-_alfaEma)*_PV_Raw)/100;

		_PV_Raw = tempVal;// after filtering
		_PV = (_PV_Hi - _PV_Lo)*(_PV_Raw - _Raw_Lo)/(_Raw_Hi - _Raw_Lo) + _PV_Lo;
		//_PV = map(val,_Raw_Lo, _Raw_Hi,_PV_Lo, _PV_Hi);
	}
	if (_CalcType == PV_SIM) _PV = _PVSim;
	return _PV;
}

void AnalogInput::setPV_Hi(float val)
{
	_PV_Hi = val;
}
float AnalogInput::getPV_Hi()
{
	return _PV_Hi;
}

void AnalogInput::setPV_Lo(float val)
{
	_PV_Lo = val;
}
float AnalogInput::getPV_Lo()
{
	return _PV_Lo;
}

void AnalogInput::setRaw_Hi(unsigned int val)
{
	_Raw_Hi = val;
}
unsigned int AnalogInput::getRaw_Hi()
{
	return _Raw_Hi;
}

void AnalogInput::setRaw_Lo(unsigned int val)
{
	_Raw_Lo = val;
}

unsigned int AnalogInput::getRaw_Lo()
{
	return _Raw_Lo;
}

unsigned int AnalogInput::getPV_Raw()
{
	return _PV_Raw;
}

void AnalogInput::setCalcType(unsigned char val)
{
	_CalcType = val;
}
unsigned char AnalogInput::getCalcType()
{
	return _CalcType;
}

void AnalogInput::setAlfaEma(unsigned char valEma){
	_alfaEma = valEma;
}

unsigned char AnalogInput::getAlfaEma(){
	return _alfaEma;
}
