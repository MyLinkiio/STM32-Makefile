#include "sys.h"

void Delay(uint_32 i)//ºÁÃëÑÓ³Ù
{
//	unsigned int temp;
//	SysTick->LOAD = 9000*i;
//	SysTick->CTRL = 0X01;
//	SysTick->VAL = 0;
//	do
//	{
//		temp = SysTick->CTRL;
//	}
//	while((temp&0x01)&&(!(temp&(1<<16))));
//	SysTick->CTRL = 0;
//	SysTick->VAL = 0;
	
	uint_32 t = 0;
	while(i--)
	{
		t = 36000;
		while(t--);
	}
	
	return;
}
