/*
  controller.h - Library untuk command
  Dibuat Oleh : Sam May 2020
*/
#ifndef controller_h
#define controller_h
#include "Arduino.h"
#include "mobileRobot.h"

class controller{
    public:
        controller(String id):_id(id){}
        void init(mobileRobot*);
        void initSenam();
        void initSenamCsv();
        void action();
        String getModeStr(){return _modeStr;}
        char getPrevMode(){return _prevMode;}
        char getPrevCmd(){return _prevCmd;}
        void attachDiagTool(diagTool *tool){_diagTool = tool;}
    private:
        String _id;
        mobileRobot* _robot2W;
        struct cmdRobot *_startSenamPtr, *_cmdPtr, *_startSenamCsvPtr;//start address for senamData
        char _prevMode, _prevCmd;
        String _modeStr, _cmdStr;
        char _iRecord;
        bool _isActionMode;
        bool _isMenu(char);
        void _execute(char);
        //private function
        diagTool *_diagTool;
        void _menuUtama();
        void _remote();
        void _senam();
        void _record();
        void _tracking();
        void _autoGaris();
        void _autoJarak();
};
#endif
