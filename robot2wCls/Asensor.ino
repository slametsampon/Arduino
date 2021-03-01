#include <NewPing.h>
#include <Servo.h>

class asensor{
  public:    
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
    int  _val;
private:
};

class sensorGaris : public asensor{
  public:
    sensorGaris(unsigned char pin);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);
  private:
    unsigned char  _pin;    
};
sensorGaris::sensorGaris(unsigned char pin): _pin(pin){
}

void sensorGaris::init(){
  //do nothings for moment 
}

int sensorGaris::getValue(){
  _val = analogRead(_pin);
  return _val;
}

boolean sensorGaris::isFree(int minVal){
  boolean flVal = true;
  this->getValue();
  if(_val <=  minVal) flVal = false;
  return flVal;
}

class sensorJarak : public asensor{
  public:
    sensorJarak(NewPing *sonarVal);
    virtual void init();
    virtual int getValue();
    virtual boolean isFree(int);

  private:
    NewPing  *_sonar;    
};
sensorJarak::sensorJarak(NewPing *sonarVal): _sonar(sonarVal){  }

void sensorJarak::init(){
  //do nothings for moment 
}

int sensorJarak::getValue(){
  _val = _sonar->ping_cm();
  return _val;
}

boolean sensorJarak::isFree(int minVal){
  boolean flVal = true;
  this->getValue();
  if(_val <=  minVal) flVal = false;
  return flVal;
}

class kepala{
  public:
    kepala(sensorJarak *sensJarak, Servo *arah);
    void init(int pinServo);
    int tengokKanan();
    int tengokKiri();
    int tengokLurus();
    boolean isTengokKananFree(int minVal);
    boolean isTengokKiriFree(int minVal);
    boolean isTengokLurusFree(int minVal);

  private:
    sensorJarak  *_sensJarak;    
    Servo *_arah;
};
kepala::kepala(sensorJarak *sensJarak, Servo *arah): _sensJarak(sensJarak),
                                                  _arah(arah){  }

void kepala::init(int pinServo){
  _arah->attach(pinServo);
}

int kepala::tengokKanan(){
  _arah->write(ORT_KANAN);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokKiri(){
  _arah->write(ORT_KIRI);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

int kepala::tengokLurus(){
  _arah->write(ORT_LURUS);
  delay(100);//memastikan posisi sdh setle
  return _sensJarak->getValue();
}

boolean kepala::isTengokKananFree(int minVal){
  this->tengokKanan();
  return _sensJarak->isFree(minVal);
}

boolean kepala::isTengokKiriFree(int minVal){
  this->tengokKiri();
  return _sensJarak->isFree(minVal);
}

boolean kepala::isTengokLurusFree(int minVal){
  this->tengokLurus();
  return _sensJarak->isFree(minVal);
}
