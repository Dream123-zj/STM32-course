//author:ora
//email:1301912993@qq.com

#include "ROTARYENCODER.h"
#include "usart.h"
#include "lcd.h"


#define ENCODER_TIM_PERIOD (u16)(65000)
#define COUNTER_RESET   (u16)30000

void rotaryEncoder_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//PA6��PA7����ģʽ
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;       
	GPIO_InitStructure.GPIO_Mode         = GPIO_Mode_AF;       
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_OD;       
	GPIO_InitStructure.GPIO_Pin         = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����GPIO����
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	

	/* Timer configuration in Encoder mode */ 
//	TIM3->PSC = 0x0;//Ԥ��Ƶ��
//	TIM3->ARR = ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ 
//	TIM3->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
//	TIM3->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
	
	//���ö�ʱ��
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//���ñ�����ģʽ
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
	
	//�������벶���˲���
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);	
		
	//���ó�ʼֵ��ʹ�ܼ�ʱ��
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��

}

