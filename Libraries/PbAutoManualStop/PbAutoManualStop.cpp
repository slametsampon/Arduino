/*
 * lihat header file PbAutoManualStop.h lebih detail
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "PbAutoManualStop.h"

PbAutoManualStop::PbAutoManualStop(String id):_id(id){}

void PbAutoManualStop::init(){
    _prevCmd = CMD_NONE;
}

String PbAutoManualStop::getId(){
    return _id;
}

char PbAutoManualStop::getCmd(bool pbAuto, bool pbManual, bool pbStop){
    char cmd = CMD_NONE;
    if(pbStop) cmd = CMD_STOP;
    else{
        if(pbManual) cmd = CMD_MANUAL;
        else if(pbAuto) cmd = CMD_AUTO;
    }
    //Hold previous value if cmd = CMD_NONE
    if (cmd == CMD_NONE) cmd = _prevCmd;
    else _prevCmd = cmd;
    
    return cmd;
}
