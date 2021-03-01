
/*	This is a default program--
	Use File->Load Prog to load a different program
*/

int count, dataLen;
unsigned long prevMilis, holdTime;
char cmd;
String temp;
String dataCsv[]={"A,3000",
"B,4000",
"C,5000",
"B,4000",
"C,5000",
"B,4000",
"C,5000",
"B,4000",
"C,5000",
"B,4000",
"C,5000",
"B,4000",
"C,5000"};

void setup()
{
	count=0;
	prevMilis = millis();
	cmd = dataCsv[0].substring(0,1);
	temp = dataCsv[0].substring(2);
	holdTime =temp.toInt();
	String test = dataCsv[0];
	int le = sizeof(test);
	dataLen = sizeof(dataCsv)/le;
}

void loop()
{
	if(millis() - prevMilis > holdTime){
		prevMilis = millis();
		count=count+1;
		if (count >= dataLen-1) count = 0;
			
		cmd = dataCsv[count].substring(0,1);
		temp = dataCsv[count].substring(2);
		holdTime =temp.toInt();
	}
}
