#include "mobile.h"
#include "controller.h"
#include "dataModel.h"
dataAccess dataRobot("record");

String dataSenamCsv[]={
	"A;2000",
    "B;4000",
    "A;2000",
    "C;2000",
    "A;2000",
    "B;4000",
    "A;2000",
    "D;1000",
    "B;2000",
    "A;4000",
    "A;5000",
    "D;5000",
    "C;5000"
};

const char delimiter =';';

void controller::init(mobileRobot* rbt){
    this->_robot2W = rbt;
    this->_prevMode = MENU_UTAMA;
    this->_prevCmd = BERHENTI;
}

//It will be run repeadly from ino
void controller::action(){
    char cmd = this->_robot2W->getCommand();
    
    //it is for one shoot running
    if (cmd != this->_prevCmd){
        this->_prevCmd = cmd;
        //cgange mode for first time
        if(this->_isMenu(cmd)){
            this->_isActionMode = false;
            this->_prevMode = cmd;
        }
    }
    //end of one shoot running

    //it will repeadly running
    this->_execute(_prevMode);
    //_diagTool->show("_prevCmd : ", "_prevMode : ",
    //                 _prevCmd, _prevMode);//(label1, label2, val1, val2)
}

void controller::initSenamCsv(){
    cmdRobot temp;
    int i;
    int delimiterPos = delimiterPos = dataSenamCsv[0].lastIndexOf(delimiter);
    int le = sizeof(dataSenamCsv[0]);
    int dataLen = sizeof(dataSenamCsv)/le;
    String tempStr;
    char cmdChar[2];//it just for one character cmd and null terminator
    //Serial.println("initSenamCsv");
    for(int count = 0; count < dataLen; count++){
		dataSenamCsv[count].toCharArray(cmdChar,4);
		tempStr = dataSenamCsv[count].substring(delimiterPos+1);
        temp.cmd=cmdChar[0];//first char for cmd
        temp.miliS=tempStr.toInt();
        i = dataRobot.add(&temp);
        if (count == 0)this->_startSenamCsvPtr = dataRobot.add(&temp);//start address for data senam
        Serial.println(count);
        Serial.print("CsvPtr : ");
        Serial.println(i);
    }
}

void controller::initSenam(){
    cmdRobot temp;
    temp.cmd=MAJU;
    temp.miliS=2000;
    dataRobot.add(&temp);
    this->_startSenamPtr = dataRobot.add(&temp);//start address for data senam

    temp.cmd=MUNDUR;
    temp.miliS=2000;
    dataRobot.add(&temp);

    temp.cmd=MAJU;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=BELOK_KANAN;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=MAJU;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=MUNDUR;
    temp.miliS=2000;
    dataRobot.add(&temp);

    temp.cmd=MAJU;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=BELOK_KIRI;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=MAJU;
    temp.miliS=1000;
    dataRobot.add(&temp);

    temp.cmd=MUNDUR;
    temp.miliS=2000;
    dataRobot.add(&temp);

    int i = _startSenamPtr;
    Serial.print("_startSenamPtr : ");
    Serial.println(i);
}

bool controller::_isMenu(char mode){
    bool isMenu = false;
    switch (mode){
        case MENU_UTAMA:  
        case REMOTE:
        case SENAM:
        case RECORD:
        case TRACKING:
        case AUTO_GARIS:
        case AUTO_JARAK:
        case STOP_AUTO:
            isMenu = true;
        break;
        default:
        break;
    }
    return isMenu;
}

void controller::_execute(char mode){
    switch (mode){
        case MENU_UTAMA: 
            this->_modeStr = "MENU_UTAMA";
            this->_menuUtama();
        break;
        case REMOTE:
            this->_modeStr = "REMOTE";
            this->_remote();
        break;
        case SENAM:
            this->_modeStr = "SENAM";
            this->_senam();
        break;
        case RECORD:
            this->_modeStr = "RECORD";
            this->_record();
        break;
        case TRACKING:
            this->_modeStr = "TRACKING";
            this->_tracking();
        break;
        case AUTO_GARIS:
            this->_modeStr = "AUTO_GARIS";
            this->_autoGaris();
        break;
        case AUTO_JARAK:
            this->_modeStr = "AUTO_JARAK";
            this->_autoJarak();
        break;
        case STOP_REMOTE:
            //it will stop all sub menu (REMOTE, AUTO_GARIS, AUTO_JARAK, RECORD)
            // and back to main_menu
            this->_robot2W->action(BERHENTI);//make sure robot stop
            this->_robot2W->setCommand(MENU_UTAMA);
            this->_isActionMode = false;
            this->_prevMode = MENU_UTAMA;
        break;
        default:
        break;
    }
}

//private function definition
void controller::_menuUtama(){
    //it's one shoot
    if(!this->_isActionMode){
        this->_prevMode = MENU_UTAMA;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
    }
}

void controller::_remote(){
    //one shoot action for _prevCmd
    if(!this->_isActionMode){
        this->_prevMode = REMOTE;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
        this->_prevCmd = BERHENTI;
        this->_robot2W->setCommand(BERHENTI);
    }

    //will stay in REMOTE's Mode until we get STOP_REMOTE command 
    this->_robot2W->action(this->_prevCmd);
  }

void controller::_senam(){
    //it is one shoot
    if(!_isActionMode){
        this->_prevMode = SENAM;
        Serial.println(this->_modeStr);
        this->_iRecord = 0;
        this->_isActionMode = true;
        _robot2W->action(RESET);
        //this->_cmdPtr = this->_startSenamPtr;//_startSenamPtr from initSenam
        this->_cmdPtr = this->_startSenamCsvPtr;//_startSenamPtr from initSenam
    }
    if ((this->_iRecord < MAX_TRACK)&&(this->_cmdPtr != NULL)){
        if (_robot2W->isMoveable()){
            _robot2W->action(RESET);
            this->_iRecord++; 
            this->_cmdPtr = this->_cmdPtr->next;
        }
        if (this->_cmdPtr != NULL) this->_robot2W->doFor(this->_cmdPtr); 
    }
    else {
        Serial.print(this->_modeStr);
        Serial.println("->COMPLETE");
        this->_robot2W->setCommand(MENU_UTAMA);
        this->_isActionMode = false;
    }
}

void controller::_record(){
    //it is one shoot
    if(!_isActionMode){
        this->_prevMode = RECORD;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
    }
    //will stay in RECORD's Mode until we get STOP_RECORD command 
}

void controller::_tracking(){
    //it is one shoot
    if(!_isActionMode){
        this->_prevMode = TRACKING;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
    }
}

void controller::_autoGaris(){
    //it is one shoot
    if(!_isActionMode){
        this->_prevMode = AUTO_GARIS;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
    }

    //will stay in AUTO_GARIS's Mode until we get STOP_AUTO command 
    //and will execute repeadly
    this->_robot2W->autoGaris();
}

void controller::_autoJarak(){
    //it is one shoot
    if(!_isActionMode){
        this->_prevMode = AUTO_JARAK;
        this->_isActionMode = true;
        Serial.println(this->_modeStr);
    }
    //will stay in AUTO_JARAK's Mode until we get STOP_AUTO command 
}
