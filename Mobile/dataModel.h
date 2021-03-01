/*
  dataModel.h - Library untuk command
  Dibuat Oleh : Sam May 2020
*/
#ifndef dataModel_h
#define dataModel_h
#include "Arduino.h"

struct cmdRobot{
  char cmd;//Command
  unsigned long miliS;//mili second
  struct cmdRobot *next; 
};
class dataAccess{
    public:
        dataAccess(String id):_id(id){}
        struct cmdRobot* add(struct cmdRobot*, struct cmdRobot*);
        void edit(struct cmdRobot*);
        void insert(struct cmdRobot*);
        void del(struct cmdRobot*);
        struct cmdRobot* read();
    private:
        String _id;
};
#endif


