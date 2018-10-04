#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"

typedef struct{
	int_16 encoderSpeed =  0;
	int_32 encoderCount = 0;
	int_32 adjustSpeed = 0;;
	float p = 0.05;
	float i = 0;
	int_32 presentErr = 0;
	int_32 lastErr = 0;
}PID_InitTypeDef;

PID_InitTypeDef PID_InitStruct;
int_32 totalDis = 0;
int_32 pwmSpeed = 0;
void EncoderInit(void );
void ExtiInit(void );
void ContrMotorspeed(int partvalue_motor_speed);
void Set_TargetMotorSpeed(int partvalue_target_speed);
void ClearTotal(void);
int_32 GetTotal(void);
#endif
