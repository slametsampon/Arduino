/*
 * lihat header file DigitalControl.h lebih detail
 * extention file harus .cpp bukan .CPP
 * April 04, 2020 : by sam
 */

/* Dependencies */
#include "DigitalControl.h"

DigitalControl::DigitalControl(String id):_id(id){}

void DigitalControl::init()
{
	_funcType = ONE_SHOOT;
}

String DigitalControl::getId()
{
	return _id;
}

void DigitalControl::setFunction(char Val)
{
	_funcType = Val;
}

char DigitalControl::getFunction()
{
	return _funcType;
}

void DigitalControl::setRelease(bool Val)
{
	_releaseSts = Val;
}

bool DigitalControl::isRelease()
{
	return _releaseSts;
}

bool DigitalControl::execute(bool inVal)
{
    bool sts = false;
    switch (_funcType) {
        case ONE_SHOOT:
            if (inVal){
                if(!_executedSts)sts = true;
            }
            else _executedSts = false;
        break;
        case HOLD_RELEASE:
            if (inVal){
                sts = true;
                _prevOutSts = sts;
            }
            else _prevOutSts = false;
            if(_releaseSts)_prevOutSts =false;
        break;
        //Transition On ONE_SHOOT
        case TRANS_ON:
            if ((!inVal) && (_prevInSts)){
                if(!_executedSts)sts = true;
            }
            else _executedSts = false;
            _prevInSts = inVal;
        break;
        case TRANS_OFF:
            if ((inVal) && (!_prevInSts)){
                if(!_executedSts)sts = true;
            }
            else _executedSts = false;
            _prevInSts = inVal;
        break;
        default:
        Serial.println("DigitalControl UNDIFINE");
        break;
    }  
    return sts;
}
