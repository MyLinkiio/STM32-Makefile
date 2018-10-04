#ifndef _CAN_H
#define _CAN_H
#include "stm32f10x.h"

void GetOrder(void);
void OpenFilter(uint32_t FilterID);
void Can_ShowShort(short Data,int Pos);
void Can_ShowFloat(float Data,int Pos);
void Can_Send(int signal);

#endif

