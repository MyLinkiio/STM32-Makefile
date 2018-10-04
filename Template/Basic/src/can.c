#include "sys.h"

/*
union
{
	char candata[2];
	short resulet;
}can_recive;
*/

extern CanTxMsg TxMess;

uint_8 order = 0;

void NVIC_Config(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;
 
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void OpenFilter(uint32_t FilterID)
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	FilterID = FilterID & 0x07FF;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	//ѡ������
	CAN_FilterInitStructure.CAN_FilterIdHigh = FilterID << 5;
	CAN_FilterInitStructure.CAN_FilterIdLow = FilterID << 5;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xFFE0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  //����λģʽ
	CAN_FilterInitStructure.CAN_FilterNumber = 1;								     //ѡ�������
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;	//ʮ��λID(11λ����)��ʮ��λID(29)
	CAN_FilterInit(&CAN_FilterInitStructure);
}

/*
void Can_ShowShort(short Data,int Pos)		//��ͨ�����з���
{
	CanTxMsg TxMessage;
	
	TxMessage.StdId=0x0002;//TFT��ʾ���ݣ�
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC=8;
	
	TxMessage.Data[0]=0xFE;
	TxMessage.Data[1]= Pos;
	TxMessage.Data[2]= *((char *)(&Data));
	TxMessage.Data[3]= *((char *)(&Data) + 1);
	TxMessage.Data[4]= 0;
	TxMessage.Data[5]= 0;
	TxMessage.Data[6]= 0;
	TxMessage.Data[7]= 0;
	
	CAN_Transmit(CAN1, &TxMessage);
}
*/

/*
void Can_ShowFloat(float Data,int Pos)	//��ͨ�����з���
{
	CanTxMsg TxMessage;
	
	TxMessage.StdId=0x0002;//TFT��ʾ���ݣ�	
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC=8;
	
	TxMessage.Data[0]=0xFD;
	TxMessage.Data[1]=Pos;
	TxMessage.Data[2] = *((char *)(&Data));
	TxMessage.Data[3] = *((char *)(&Data) + 1);
	TxMessage.Data[4] = *((char *)(&Data) + 2);
	TxMessage.Data[5] = *((char *)(&Data) + 3);
	TxMessage.Data[6] = *((char *)(&Data) + 2);
	TxMessage.Data[7] = *((char *)(&Data) + 3);	
	
	CAN_Transmit(CAN1, &TxMessage);
}
*/

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	
	if(RxMessage.Data[0] == 0xBB)
	{
		order = RxMessage.Data[1];
	}
	
	return;
}

void GetOrder(void)
{
	return order;
}

void Can_Send(int signal){
	CanTxMsg TxMessage;
	
	TxMessage.StdId=0x0002;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC=8;
	
	TxMessage.Data[0]=0xFE;
	TxMessage.Data[1]= signal;
	TxMessage.Data[2]= 0;
	TxMessage.Data[3]= 0;
	TxMessage.Data[4]= 0;
	TxMessage.Data[5]= 0;
	TxMessage.Data[6]= 0;
	TxMessage.Data[7]= 0;
	
	CAN_Transmit(CAN1, &TxMessage);
}

void CanInit(void)
{
	GPIO_InitTypeDef			GPIO_InitStructure;
	CAN_InitTypeDef       CAN_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
	
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	
	CAN_InitStructure.CAN_ABOM = DISABLE;				//�Ƿ�ʹ���Զ����߹���
	CAN_InitStructure.CAN_AWUM = DISABLE;				//�Ƿ�ʹ��˯���Զ�����
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;							//Ӱ�첨����
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;							//Ӱ�첨����
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;					//����ģʽ
	CAN_InitStructure.CAN_NART = DISABLE;				//�Ƿ�ʹ�÷��Զ��ش���
	CAN_InitStructure.CAN_Prescaler = 6;				//Ӱ�첨����					48M/((7+8+1)*6)=500K
	CAN_InitStructure.CAN_RFLM = DISABLE;				//�Ƿ�ʹ��FIFO���������Ǿ����ݣ�
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		//����ͬ����Ծ��ȣ�Ӱ�첨���ʣ�
	CAN_InitStructure.CAN_TTCM = DISABLE;				//�Ƿ�ʹ��ʱ�䴥��ģʽ
	CAN_InitStructure.CAN_TXFP = DISABLE;				//�Ƿ�ʹ�÷������ȼ�����ID������
	
	CAN_Init(CAN1,&CAN_InitStructure);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	NVIC_Config();
	OpenFilter(0x0004);
}
