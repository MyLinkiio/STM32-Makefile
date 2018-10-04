#ifndef __LEG_H
#define __LEG_H
include "sys.h"

//motor rotate dir ///////////////////////////
#define RIGHT_MASTER_MOTOR_DIR 1
#define STAND_BY 0
#define MASTER_ROTATE 1
void MasterNodeRun(uint_8 flag);
////////////////////////////////////////////////////



////////////////////////////////////////////////
#define RIGHT_MASTER_MOTOR_DIR 1
#define STAND_BY 0
#define SLAVE_NODE_UP 1
#define SLAVE_NODE_DOWN 2
void SlaveNodeRun(uint_8 flag);
////////////////////////////////////////////
#endif