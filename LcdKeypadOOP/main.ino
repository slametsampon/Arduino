void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // following line sets the RTC to the date & time this sketch was compiled
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  //attach serialCommands
  controller.attachCmdIn(&serInput);//attach serInput to controller, use address instead of varible
  controller.attachCmdIn(&keyPad);//attach keyPad to controller, use address instead of varible

  controller.pasangModelMenu(&accessMenuUtama);//attach model menu to controller, use address instead of varible
  controller.pasangModelParameter(&accessParameter);//attach model parameter to controller, use address instead of varible
  controller.pasangView(&view);//attach view to controller, use address instead of varible

  setupMenuUtama();
  setupParameter();
}

void loop() {
  // put your main code here, to run repeatedly:
  sequenceUtama.execute();
  if (sequenceUtama.isASecondEvent()){
    digitalWrite( LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1 );

    //time keeping
    waktuSekarang = rtc.now();
    char waktuFrm[] = "DDMMYY-hh:mm:ss";
    waktu = waktuSekarang.toString(waktuFrm);
  }
  controller.menu();
}
