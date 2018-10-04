#include "sys.h"

void EncoderInit(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);  

	TIM_TimeBaseStructure.TIM_Prescaler = 0;   
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE); 
	TIM3->CNT = 0;
}

void ExtiInit(void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler = 360;  
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = 999;    
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
}

void TIM2_IRQHandler(void){	
	PID_InitStruct.encoderSpeed = (int_16)(TIM3->CNT); 
	TIM3->CNT = 0;
	PID_InitStruct.presentErr = pwmSpeed - PID_InitStruct.encoderSpeed;
	PID_InitStruct.adjustSpeed += PID_InitStruct.presentErr * P + PID_InitStruct.lastErr * I;
	PID_InitStruct.lastErr = PID_InitStruct.presentErr;
	ContrMotorspeed((int_32)PID_InitStruct.adjustSpeed);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void ContrMotorspeed(int partvalue_motor_speed)
{
	if(partvalue_motor_speed > 0)
	{
		TIM1->CCER = 0x0580;
	}
	else if(partvalue_motor_speed < 0)
	{
		TIM1->CCER = 0x0850;
		partvalue_motor_speed = -partvalue_motor_speed;
	}
	
	partvalue_motor_speed = 700 - partvalue_motor_speed;
	
	if(partvalue_motor_speed <= 10) {partvalue_motor_speed = 10;}
	
	TIM1->CCR2 = partvalue_motor_speed;
	TIM1->CCR3 = partvalue_motor_speed;
}

void Set_TargetMotorSpeed(int partvalue_target_speed)
{
	can_motor_speed = partvalue_target_speed;
	return;
}

void ClearTotal(void)
{
	totalDis = 0;
	
	return;
}

int_32 GetTotal(void)
{
	return totalDis;
}