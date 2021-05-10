/*
 * lihat header file Comparator.h lebih detail
 * extention file harus .cpp bukan .CPP
 * May 10, 2021 : by sam
 */

/* Dependencies */
#include "comparator.h"

Comparator::Comparator(String id):_id(id){}

void Comparator::init()
{
	_funcType = GREATER_THAN;
}

void Comparator::setFunction(char Val)
{
	_funcType = Val;
}

bool Comparator::execute(float inVal)
{
    bool sts = false;
    /*
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
    */
    return sts;
}
