/*
  AnalogInput.h - Library untuk AnalogInput
  Dibuat Oleh : Sam May 2017
*/
#ifndef AnalogInput_h
#define AnalogInput_h

#include "Arduino.h"

#define NOT_INIT	255	//Not initilization yet
#define NOT_INIT_VAL	65535	//Not initilization yet
#define ANALOG_INP	1	//Analog input 
#define ANALOG_OUT	2	//Analog output
#define DIGIT_INP	3	//Digital input
#define DIGIT_OUT	4	//Digital output
#define PV_AUTO	1	//PV value from physical input and Calculate
#define PV_SIM	2	//PV value from simulation, given by other
#define NO_ERR	0	//tidak ada error
#define PIN_ERR	1	//PIN belum terisi
#define TYPE_ERR	2	//Type AnalogInput (Analog In/Out, Digital In/Out) belu terisi
#define PV_HI_ERR	4	//PV High belum terisi
#define PV_LO_ERR	8	//PV Low belum terisi
#define RAW_HI_ERR	16	//RAW High belum terisi
#define RAW_LO_ERR	32	//RAW Low belum terisi

class AnalogInput
{
  public:
    AnalogInput(String id);
    unsigned char Init();
    void setUnit(String unit);
    void setPin(unsigned char pin);
    void setPVSim(float val);
    void setPV_Hi(float val);
    void setPV_Lo(float val);
    void setRaw_Lo(unsigned int val);
    void setAlfaEma(unsigned char);
    void setRaw_Hi(unsigned int val);
    void setCalcType(unsigned char CalcType);
    void setTagType(unsigned char TagType);
    String getId();
    String getUnit();
    unsigned char getPin();
    float getPV();
    float getPV_Hi();
    float getPV_Lo();
    unsigned int getPV_Raw();
    unsigned int getRaw_Hi();
    unsigned int getRaw_Lo();
    unsigned char getAlfaEma();
    unsigned char getCalcType();
    unsigned char getTagType();
    unsigned char getErr();
  private:
    String _id;
    String _unit;
    unsigned char _pin;
    float _PV;
    float _PV_Hi;
    float _PV_Lo;
    float _PVSim;
    unsigned int _PV_Raw;
    unsigned int _Raw_Hi;
    unsigned int _Raw_Lo;
    unsigned char _CalcType;
    unsigned char _TagType;
    unsigned char _Err;
    unsigned char _alfaEma;//alfa for EMA Filter (0 - 100) in percentage
};

#endif