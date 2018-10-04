#include "sys.h"

void BspInit(void){
	PwmInit();
	EncoderInit();
	ExtiInit();
	CanInit();
}


int main(){
	BspInit();
	Delay(500);
	while(1){
		//this master program
		Can_Send(SLAVE_LEG_UP);


		int signal =  CAN_RECEIVE()
		SlaveNodeRun(signal);
		Can_Send(0xaa);


		while(!GetOrder() == 0xaa)
			;

		Can_Send(MASTER_LEG_ROTATE);


		int signal =  CAN_RECEIVE()
		MasterNodeRun(signal);
		Can_Send(0xaa);

		while(!GetOrder())
			;

		Can_Send(SLAVE_LEG_DOWN);

		int signal =  CAN_RECEIVE()
		SlaveNodeRun(signal);
		Can_Send(0xaa);

		
		while(!GetOrder())
			;

	}
}