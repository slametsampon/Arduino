#include "SchedulerOnOff.h"

SchedulerOnOff lampuNagaSelatan(ONESHOOT_TYPE);
//SchedulerOnOff lampuNagaTengah(ONESHOOT_TYPE);
//SchedulerOnOff lampuNagaUtara(ONESHOOT_TYPE);
SchedulerOnOff pompaEmergencyHydroponic(CYCLYC_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lampuNagaSelatan.setInitialStartHour(5);//5 jam setelah magrib (5 + 5 = jam 10 malam)
  lampuNagaSelatan.setInitialStartMinute(5);//5 jam setelah magrib (5 + 5 = jam 10 malam)
  lampuNagaSelatan.setInitialStartSecond(5);//5 jam setelah magrib (5 + 5 = jam 10 malam)
  lampuNagaSelatan.setDurationOnMinute(90);//nyala selama 90 menit
  lampuNagaSelatan.setActive(true);

  //lampuNagaTengah.setInitialStartHour(6);//6 jam setelah magrib (5 + 6 = jam 11 malam)
  //lampuNagaTengah.setDurationOnMinute(90);//nyala selama 90 menit

  //lampuNagaUtara.setInitialStartHour(7);//7 jam setelah magrib (5 + 7 = jam 12 malam)
  //lampuNagaUtara.setDurationOnMinute(90);//nyala selama 90 menit

  pompaEmergencyHydroponic.setPeriodeSecond(5);//5 detik setelah pompa mati(karena listrik atau sebab yang lain)
  pompaEmergencyHydroponic.setDurationOnSecond(3);//nyala selama 1 detik
  pompaEmergencyHydroponic.setActive(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long periodTime,prevMilli,currMilli,cycleEnd;
  int countEr=0;
  lampuNagaSelatan.execute();
  //lampuNagaTengah.execute();
  //lampuNagaUtara.execute();

  Serial.print("lampuNagaSelatan.getInitialStartTime() : ");
  Serial.println(lampuNagaSelatan.getInitialStartTime());
  Serial.print("lampuNagaSelatan.getDurationOn(): ");
  Serial.println(lampuNagaSelatan.getDurationOn());

  prevMilli = millis();
  cycleEnd = prevMilli + 3*pompaEmergencyHydroponic.getPeriodeTime();
  Serial.print("Start Time: ");
  Serial.print(prevMilli);
  Serial.print(" cycleEnd : ");
  Serial.println(cycleEnd);
  while(currMilli <= cycleEnd){
    currMilli = millis();

//...........tempat uji..............

    if (pompaEmergencyHydroponic.execute()) Serial.println("Status : True");
    else Serial.println("Status : False");

//...........tempat uji...............
  }
  Serial.print("End Time: ");
  Serial.println(millis());
delay(60000);
}
