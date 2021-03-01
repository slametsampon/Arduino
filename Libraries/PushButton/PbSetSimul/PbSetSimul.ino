#define PIN_AUTO    2//Pin Device Input Auto
#define PIN_MANUAL  3//Pin Device Input Manual
#define PIN_STOP    4//Pin Device Input Stop

class DEVICE{
  public:
    DEVICE(char pin):_pin(pin){}
    
    void init(){
        pinMode(_pin, INPUT_PULLUP);
    }

    bool getVal(){
        return(digitalRead(_pin));
    }

    char getPin(){
        return _pin;
    }
  
  private:
    char _pin;
    String _id;
};

#define MAX_DEVIN   9//MAximum decives input attached

class PbSet{
  public:
    static unsigned char devInNbr;
    DEVICE *digIn[MAX_DEVIN];
    PbSet(String id):_id(String(id)){}

    static unsigned char getDevInNbr(){
        return devInNbr;
    }

    void init(){
      _prevCmd = 0;
    }

    void attachIn(DEVICE *_devIn){
        digIn[devInNbr] = _devIn;
        _devIn->init();
        devInNbr++;
    }

    char getCmd(){
      //get the highest number of active input
      int i=devInNbr;
      while( i > 0){
          if (!digIn[i-1]->getVal())break;//break from loop if active
          i--;
      }
      if (i == 0) i = _prevCmd;
      else _prevCmd = i;
      return i;
    }
  private:
    String _id;
    char _prevCmd;
};

//------
DEVICE  pbAuto(PIN_AUTO);
DEVICE  pbManual(PIN_MANUAL);
DEVICE  pbStop(PIN_STOP);
PbSet   PB("PB Set");

int cmd;
unsigned char PbSet::devInNbr=0;
void setup(){
    Serial.begin(9600);
    //Init for have been taken in attachIn methode
    PB.attachIn(&pbAuto);
    PB.attachIn(&pbManual);
    PB.attachIn(&pbStop);
}

void loop(){
    cmd = PB.getCmd();
    Serial.print("cmd : ");
    Serial.println(cmd);

    delay(5000);
}
