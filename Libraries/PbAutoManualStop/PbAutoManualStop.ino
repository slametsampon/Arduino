/*
 * lihat header file PbAutoManualStop.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "PbAutoManualStop.h"

PbAutoManualStop PB("PB Set");
int cmd;
boolean _pbAuto, _pbManual, _pbStop;

void setup()
{
	pinMode(02, INPUT);
	pinMode(03, INPUT);
	pinMode(04, INPUT);
}

void loop()
{
	_pbAuto = digitalRead(02);
	_pbManual = digitalRead(03);
	_pbStop = digitalRead(04);
    cmd = PB.getCmd(_pbAuto, _pbManual, _pbStop);

    Serial.print("Cmd : ");
    Serial.println(cmd);
	}
