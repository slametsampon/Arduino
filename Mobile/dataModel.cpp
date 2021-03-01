#include "dataModel.h"
struct cmdRobot* frontCmdSenam = NULL;
struct cmdRobot* rearCmdSenam = NULL;
struct cmdRobot* frontCmdTrack = NULL;
struct cmdRobot* rearCmdTrack = NULL;

struct cmdRobot* dataAccess::add(cmdRobot* prevrcd, cmdRobot* rcd){
  struct cmdRobot* temp;
   if (prevrcd == NULL) {
      prevrcd = (struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      prevrcd->next = NULL;
      prevrcd->cmd = rcd->cmd;
      prevrcd->miliS = rcd->miliS;
   } else {
      temp=(struct cmdRobot *)malloc(sizeof(struct cmdRobot));
      prevrcd->next = temp;
      temp->cmd = rcd->cmd;
      temp->miliS = rcd->miliS;
      temp->next = NULL;
      prevrcd = temp;
   }
   return prevrcd;
}

void dataAccess::edit(cmdRobot* rcd){

}

void dataAccess::insert(cmdRobot* rcd){

}

void dataAccess::del(cmdRobot* rcd){

}

cmdRobot* dataAccess::read(){

}