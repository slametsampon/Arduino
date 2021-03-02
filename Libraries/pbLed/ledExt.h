/*
  LedExt.h - Library for Led Extended
  Led with multiple functionality (on, off, blink)
  By : Sam March 01, 2021
*/
#ifndef ledExt_h
#define ledExt_h

  class LedExt{
    public:
      LedExt(char);
      void init();
      void on();
      void off();
      void blink(unsigned long);

    private:
      unsigned long  _prevMilli;//in milli second
      char  _pin;
  };

#endif
