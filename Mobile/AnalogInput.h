/*
  AnalogInput.h - Library untuk AnalogInput
  Dibuat Oleh : Sam May 2017
*/
#ifndef AnalogInput_h
#define AnalogInput_h

#include "Arduino.h"

#define PV_AUTO	1	//PV value from physical input and Calculate
#define PV_SIM	2	//PV value from simulation, given by other

class AnalogInput
{
  public:
    AnalogInput(char);
    void Init();
    void setUnit(String unit);
    void setPVSim(float val);
    void setPV_Hi(float val);
    void setPV_Lo(float val);
    void setRaw_Lo(unsigned int val);
    void setAlfaEma(unsigned char);
    void setRaw_Hi(unsigned int val);
    void setCalcType(unsigned char CalcType);
    String getUnit();
    char getPin();
    float getPV();
    float getPV_Hi();
    float getPV_Lo();
    unsigned int getPV_Raw();
    unsigned int getRaw_Hi();
    unsigned int getRaw_Lo();
    unsigned char getAlfaEma();
    unsigned char getCalcType();
  private:
    String _unit;
    char _pin;
    float _PV;
    float _PV_Hi;
    float _PV_Lo;
    float _PVSim;
    unsigned int _PV_Raw;
    unsigned int _Raw_Hi;
    unsigned int _Raw_Lo;
    unsigned char _CalcType;
    unsigned char _TagType;
    unsigned char _alfaEma;//alfa for EMA Filter (0 - 100) in percentage
};

#endif