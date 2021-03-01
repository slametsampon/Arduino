class Event {
  public:
    virtual void handle() = 0;
    void info(){
      Serial.println("EventBase");
    }
};

class EventLeft : public Event {
  public:
    void handle();
} leftEvent;

void EventLeft::handle(){
      Serial.println("EventRight");
    }

class EventRight : public Event {
  public:
    void handle();
} rightEvent;

void EventRight::handle(){
      Serial.println("EventRight");
    }


class PushButton {
  public:
    PushButton(int8_t _pin, Event * _event) : pin(_pin), state(true), event(_event) {
      pinMode(pin, INPUT_PULLUP);
    }

    void check() {
      if (! digitalRead(pin)) { // inverted logic
        if (state) event->handle();
        state = false;
      } else {
        state = true;
      }
      event->info();
    }

  private:
    int8_t    pin;
    bool    state;
    Event * event;
};

PushButton buttons[] = {
  {4, &leftEvent},
  {5, &rightEvent}
};

void setup()   {    
  Serial.begin(9600);
}

void loop() {
  delay(1000);

  for (PushButton & button : buttons) button.check();
  //// if the range based for loop above doesn't work, you have to use old school one:
  // for (uint8_t i = 0; i < 2; ++i) buttons[i].check();
}
