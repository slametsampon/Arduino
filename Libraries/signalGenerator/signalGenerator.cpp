/*
 * lihat header file signalGenerator.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "signalGenerator.h"
#include "Arduino.h"
float signalGenerator::calculateValue(){
  _value = (float(_valueRaw) / 0xFF)*(_maxValue - _minValue) + _minValue;
  return _value;
}
float signalGenerator::signalRandom(){
  _valueRaw = random(0xFF);// berikan nilai max 16 bit full high
  return calculateValue();
}

float signalGenerator::signalCosinus(){
  float ramp = 360.0/float(_periodTime);
  unsigned long tempTime = millis();
  float degree = ramp*(tempTime - _startCycle)+_phaseShift;// in degree

  if (degree < 0) degree = degree + 360.0;
  if (degree > 360.0) degree = int(degree) % 360;

  float _radian = degree * DEG_TO_RAD;// in radian
  
  if ((tempTime - _startCycle) < _periodTime) _valueRaw = (cos(_radian)+1)*float(0xFF/2); 
  else _valueRaw = 0xFF;              
  if ((tempTime - _startCycle) >= _periodTime) {
    _startCycle = tempTime;// start new cycle
    _valueRaw = 0xFF;              
  }
  return calculateValue();
}
float signalGenerator::signalSinus(){
  float ramp = 360.0/float(_periodTime);
  unsigned long tempTime = millis();
  float degree = ramp*(tempTime - _startCycle)+_phaseShift;// in degree

  if (degree < 0) degree = degree + 360.0;
  if (degree > 360.0) degree = int(degree) % 360;

  float _radian = degree * DEG_TO_RAD;// in radian
  
  if ((tempTime - _startCycle) < _periodTime) _valueRaw = (sin(_radian)+1.0)*float(0xFF/2); 
  else _valueRaw = 0xFF/2;              
  if ((tempTime - _startCycle) >= _periodTime) {
    _startCycle = tempTime;// start new cycle
    _valueRaw = 0xFF/2;// back value to centre
  }
  return calculateValue();
}
float signalGenerator::signalSquare(){
  unsigned long downTime = _periodTime * float(100 - _percentCycle)/100.0;
  unsigned long tempTime = millis();
  
  if ((tempTime - _startCycle) <= downTime) _valueRaw = 0; 
  else _valueRaw = 0xFF;              
  if ((tempTime - _startCycle) >= _periodTime) {
    _startCycle = tempTime;// start new cycle
    _valueRaw = 0;// back value to 0
  }
  return calculateValue();
}
float signalGenerator::signalTriangle(){
  float ramp = float(0xFF)/float(_periodTime/2);
  unsigned long tempTime = millis();
  byte incDec = ramp*(tempTime - _prevMilliSegi3);//milli detik
  _prevMilliSegi3 = tempTime;
  
  if ((tempTime - _startCycle) <= _periodTime/2){
    if ((0xFF - _valueRaw) < incDec )_valueRaw = 0xFF; 
    else _valueRaw = _valueRaw + incDec;              
  }
  else {
    if (_valueRaw < incDec )_valueRaw = 0; 
    else _valueRaw = _valueRaw - incDec;              
  }
  
  if ((tempTime - _startCycle) >= _periodTime) {
    _startCycle = tempTime;// start new cycle
    _valueRaw = 0;// back value to 0
  }

  return calculateValue();
}
float signalGenerator::signalSawTooth(){
  float ramp = float(0xFF)/float(_periodTime);
  unsigned long tempTime = millis();
  byte incDec = ramp*(tempTime - _prevMilliSaw);//milli detik
  _prevMilliSaw = tempTime;
  
  if ((tempTime - _startCycle) <= _periodTime) {
    if ((0xFF - _valueRaw) < incDec )_valueRaw = 0xFF; 
    else _valueRaw = _valueRaw + incDec;              
  }
  else if ((tempTime - _startCycle) >= _periodTime) {
    _startCycle = tempTime;// start new cycle
    _valueRaw = 0;// back value to 0
  }
  return calculateValue();
}

signalGenerator::signalGenerator(byte val){
  _signalType = val;
  _active = true;
  _runCycle = DEFAULT_RUN_CYCLE;// mili detik 
  _prevMilli = millis();
  _startCycle = _prevMilli;
  _prevMilliSegi3=_prevMilli;  
  _prevMilliSaw=_prevMilli;  
  _phaseShift = 0;
}

boolean signalGenerator::isFlRun(){
  unsigned long currMilli = millis();
  if ((currMilli - _prevMilli) >= _runCycle){
    _prevMilli = currMilli;
    _flRun = true;
  }
return _flRun;
}
float signalGenerator::execute(){
  if (_active && isFlRun()){
    _flRun = false;   
    switch (_signalType){
      case RANDOM_TYPE:
        return signalRandom();
      break;
      case SIN_TYPE:
        return signalSinus();
      break;
      case COS_TYPE:
        return signalCosinus();
      break;
      case TRIANGLE_TYPE:
        return signalTriangle();
      break;
      case SAWTOOTH_TYPE:
        return signalSawTooth();
      break;
      case SQUARE_TYPE:
        return signalSquare();
      break;
      default:
      break;
    }  
  }
  if (!_active)return 0;
}

void signalGenerator::setRunCycle(byte val){
  _runCycle = val;  
}
byte signalGenerator::getRunCycle(){
  return _runCycle;  
}

float signalGenerator::getValue(){
  return _value;
}
byte signalGenerator::getValueRaw(){
  return _valueRaw;
}

float signalGenerator::getPhaseShift(){
  return _phaseShift;
}
void signalGenerator::setPhaseShift(float val){
  _phaseShift = val;
}

void signalGenerator::setPeriodTime(unsigned long val){
  _periodTime = val;  
}
unsigned long signalGenerator::getPeriodTime(){
  return _periodTime;  
}

void signalGenerator::setMaxValue(float val){
  _maxValue = val;  
}
float signalGenerator::getMaxValue(){
  return _maxValue;  
}

void signalGenerator::setMinValue(float val){
  _minValue = val;  
}
float signalGenerator::getMinValue(){
  return _minValue;  
}

void signalGenerator::setSignalType(byte val){
  _signalType = val;  
}
byte signalGenerator::getSignalType(){
  return _signalType;  
}

void signalGenerator::setPercentCycle(byte val){
  _percentCycle = val;  
}
byte signalGenerator::getPercentCycle(){
  return _percentCycle;  
}

void signalGenerator::setActive(boolean val){
  _active = val;  
}
byte signalGenerator::isActive(){
  return _active;  
}

