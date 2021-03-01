/*
 * lihat header file Comparator.h lebih detail
 * extention file harus .cpp bukan .CPP
 * April 04, 2020 : by sam
 */

/* Dependencies */
#include "Comparator.h"
//#include "Arduino.h"

Comparator::Comparator(String id):_id(id){}

void Comparator::init()
{
	_funcType = GREATER_THAN;
}

void Comparator::setUnit(String unitVal)
{
	_unit = unitVal;
}

String Comparator::getUnit()
{
	return _unit;
}

void Comparator::setFunction(char Val)
{
	_funcType = Val;
}

char Comparator::getFunction()
{
	return _funcType;
}

void Comparator::setHigh(float setHigh)
{
	_setHigh=setHigh;
}

float Comparator::getHigh()
{
	return _setHigh;
}

void Comparator::setLow(float setLow)
{
	_setLow=setLow;
}

float Comparator::getLow()
{
	return _setLow;
}

unsigned char Comparator::getErr()
{
	return _Err;
}

bool Comparator::execute(float inVal)
{
    bool sts = false;
    switch (_funcType) {
        case EQUAL:
            if ((inVal == _setLow) ||(inVal == _setHigh))sts = true;
        break;
        case HYSTERISYS:
            if (inVal > _setLow){
                sts = true;
                _prevSts = sts;
            }
            if ((inVal > _setLow) && (inVal < _setHigh))sts = _prevSts;
            if (inVal < _setLow){
                sts = false;
                _prevSts = sts;
            }
        break;
        case LESS_THAN:
            if (inVal < _setLow)sts = true;
        break;
        case GREATER_THAN:
            if (inVal > _setLow)sts = true;
        break;
        default:
        Serial.println("Comparator UNDIFINE");
        break;
    }  
    return sts;
}
