#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"
#include "can.h"
#include "encoder.h"
#include "pwm.h"
#include "delay.h"
#include "stdlib.h"
#include "leg.h"

//This is can's order list (custom)
#define MASTER_LEG_ROTATE 0xA1



#define SLAVE_LEG_UP 0xB1
#define SLAVE_LEG_DONW 0xB2
#define STAND_BY 0xC1

//#defien 
#define	RECIVE_POS		20000
#define SHOOT_SPEED 	1000
#define SHOOT_POS		15000

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long uint_64;
typedef short int_16;
typedef int int_32;
typedef long int_64;
#endif

