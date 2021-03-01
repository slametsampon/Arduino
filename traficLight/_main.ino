LED liveLed(PIN_LED_LIVE);
LED UtaraRedLed(RED_UTARA);
LED UtaraYlwLed(YELLOW_UTARA);
LED UtaraGrnLed(GREEN_UTARA);
LED UtaraGndLed(GROUND_UTARA);
TL  tlUtara(&UtaraRedLed, &UtaraYlwLed,
            &UtaraGrnLed, &UtaraGndLed);

LED TimurRedLed(RED_TIMUR);
LED TimurYlwLed(YELLOW_TIMUR);
LED TimurGrnLed(GREEN_TIMUR);
LED TimurGndLed(GROUND_TIMUR);
TL  tlTimur(&TimurRedLed, &TimurYlwLed,
            &TimurGrnLed, &TimurGndLed);

LED BaratRedLed(RED_BARAT);
LED BaratYlwLed(YELLOW_BARAT);
LED BaratGrnLed(GREEN_BARAT);
LED BaratGndLed(GROUND_BARAT);
TL  tlBarat(&BaratRedLed, &BaratYlwLed,
            &BaratGrnLed, &BaratGndLed);

unsigned char seqTimer::SeqNbr = 0;
seqTimer utaraSeqGreen;
seqTimer utaraSeqYellow;
seqTimer timurSeqGreen;
seqTimer timurSeqYellow;
seqTimer baratSeqGreen;
seqTimer baratSeqYellow;
unsigned char seqAll = 1;

void setup() {
  Serial.begin(9600);
  liveLed.init();
  
  intLedUtara();
  intLedTimur();
  intLedBarat();
  
}

void loop() {
  //liveLed.blink();
  seqTL();

  seqAction();
}
void intLedUtara(){
  UtaraRedLed.init();
  UtaraYlwLed.init();
  UtaraGrnLed.init();
  UtaraGndLed.init();
  UtaraGndLed.off();
}
void intLedTimur(){
  TimurRedLed.init();
  TimurYlwLed.init();
  TimurGrnLed.init();
  TimurGndLed.init();
  TimurGndLed.off();
}
void intLedBarat(){
  BaratRedLed.init();
  BaratYlwLed.init();
  BaratGrnLed.init();
  BaratGndLed.init();
  BaratGndLed.off();
}

void seqTL(){
  utaraSeqGreen.doFor(15000, &seqAll);
  utaraSeqYellow.doFor(1000, &seqAll);
  timurSeqGreen.doFor(10000, &seqAll);
  timurSeqYellow.doFor(1000, &seqAll);
  baratSeqGreen.doFor(5000, &seqAll);
  baratSeqYellow.doFor(1000, &seqAll);
}
void seqAction(){
  switch (seqAll){
    case 1:
      tlUtara.greenOn();
      tlTimur.redOn();
      tlBarat.redOn();
    break;
    case 2:
      tlUtara.yellowOn();
      tlTimur.redOn();
      tlBarat.redOn();
    break;
    case 3:
      tlUtara.redOn();
      tlTimur.greenOn();
      tlBarat.redOn();
    break;
    case 4:
      tlUtara.redOn();
      tlTimur.yellowOn();
      tlBarat.redOn();
    break;
    case 5:
      tlUtara.redOn();
      tlTimur.redOn();
      tlBarat.greenOn();
    break;
    case 6:
      tlUtara.redOn();
      tlTimur.redOn();
      tlBarat.yellowOn();
    break;
    default:
      tlUtara.yellowBlink();
      tlTimur.yellowBlink();
      tlBarat.yellowBlink();
    break;
  }
}
