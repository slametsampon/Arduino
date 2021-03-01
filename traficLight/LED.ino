class tlLight{
  public:    
    virtual void init();
    virtual void on();
    virtual void off();
    virtual void blink();
};

class LED : public tlLight{
  public:
    LED(char pin);
    virtual void init();
    virtual void on();
    virtual void off();
    virtual void blink();

  private:
    unsigned long  _prevMilli;
    char  _pin;
};
LED::LED(char pin):_pin(pin){}
void LED::init(){
  pinMode(_pin, OUTPUT);
}
void LED::on(){
  digitalWrite(_pin, HIGH);
}
void LED::off(){
  digitalWrite(_pin, LOW);
}
void LED::blink(){
  if ((millis() - _prevMilli) >= BLINK_TIME){
    _prevMilli = millis();
    digitalWrite( _pin, digitalRead(_pin) ^ 1 );
  }
}

class TL{
  public:
    TL(LED *red, LED *ylw, LED *grn, LED *gnd);
    void redOn();
    void yellowOn();
    void yellowBlink();
    void greenOn();
  private:
    LED  *_ledRed, *_ledYellow, *_ledGreen, *_ground;
};

TL::TL(LED *red, LED *ylw, LED *grn, LED *gnd):_ledRed(red),
   _ledYellow(ylw), _ledGreen(grn), _ground(gnd){}
void TL::redOn(){
  _ledRed->on();
  _ledYellow->off();
  _ledGreen->off();
  _ground->off();
}
void TL::yellowOn(){
  _ledRed->off();
  _ledYellow->on();
  _ledGreen->off();
  _ground->off();
}
void TL::yellowBlink(){
  _ledRed->off();
  _ledYellow->blink();
  _ledGreen->off();
  _ground->off();
}
void TL::greenOn(){
  _ledRed->off();
  _ledYellow->off();
  _ledGreen->on();
  _ground->off();
}
