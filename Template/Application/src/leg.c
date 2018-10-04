#include "leg.h"

void MasterNodeRun(uint_8 flag){
	if(flag == MASTER_ROTATE){
		ContrMotorspeed(200);
		Delay(300);
		ContrMotorspeed(0);
	}

	else
		ContrMotorspeed(0);
}


void SlaveNodeRun(uint_8 flag){
	if(flag == SLAVE_NODE_UP){
		ContrMotorspeed(200);
		Delay(300);
		ContrMotorspeed(0);
	}

	else if(flag == SLAVE_NODE_DOWN){
		ContrMotorspeed(-200);
		Delay(300);
		ContrMotorspeed(0);
	}

	else
		ContrMotorspeed(0);
}