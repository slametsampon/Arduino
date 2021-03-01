class seqTimer{
  public:    
    static unsigned char SeqNbr;
    
    seqTimer();
    void doFor(unsigned long msVal, unsigned char *seqVal);

    static unsigned char getSeqNbr(){
      return SeqNbr;
    }

  private:    
    unsigned char _id;
    unsigned long  _prevMilli;
};
seqTimer::seqTimer(){
    SeqNbr++;//naikkan jumlah seqNbr
    _id = SeqNbr;
  }

void seqTimer::doFor(unsigned long msVal, unsigned char *seqVal){
  if (*seqVal == _id){
    if (_prevMilli == 0){
      _prevMilli = millis();
    }
    if ((millis() - _prevMilli) >= msVal){
      (*seqVal)++;// it is not same with *seqVal++
      if (*seqVal > SeqNbr)*seqVal = 1;
      _prevMilli = 0;
    }
  }
}
