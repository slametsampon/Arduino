
/*	This is a default program--
	Use File->Load Prog to load a different program
*/

//Kode Perintah
#define   CMD_NONE          0 //Command None 
#define   CMD_AUTO          1 //Command Auto
#define   CMD_MANUAL        2 //Command Manual
#define   CMD_STOP          3 //Command Stop

int prevCmd,pbRaw,cmd,genCmd;
boolean _pbAuto, _pbManual, _pbStop;
void setup()
{
	pinMode(02,INPUT);
	pinMode(03,INPUT);
	pinMode(04,INPUT);
	prevCmd = CMD_NONE;
	genCmd = CMD_NONE;
	Serial.begin(9600);
}

int getCmd(bool pbAuto, bool pbManual, bool pbStop){
	char rawCmd=CMD_NONE;
	if(pbStop) rawCmd = CMD_STOP;
		else{
				if(pbManual) rawCmd = CMD_MANUAL;
				else if(pbAuto) rawCmd = CMD_AUTO;
			}
	pbRaw = rawCmd;
	//It's for holding previous value if pbRaw is CMD_NONE
	if (rawCmd == CMD_NONE)rawCmd = prevCmd;
	else prevCmd = rawCmd;
	return rawCmd;
}
	
void loop()
{
	_pbAuto = digitalRead(02);
	_pbManual = digitalRead(03);
	_pbStop = digitalRead(04);
	cmd = getCmd(_pbAuto, _pbManual, _pbStop);
	if(cmd != genCmd){
		genCmd = cmd;
		if (cmd == CMD_STOP)Serial.println("CMD_STOP");
		if (cmd == CMD_MANUAL)Serial.println("CMD_MANUAL");
		if (cmd == CMD_AUTO)Serial.println("CMD_AUTO");
	}
}
