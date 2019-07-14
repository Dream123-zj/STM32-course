


#include "timer.h"


void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//��������
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//��������


	/* Timer configuration in Encoder mode */ 
	TIM3->PSC = 0x0;//Ԥ��Ƶ��
	TIM3->ARR = ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ 
	TIM3->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM3->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM3->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM3->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM3->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM3->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM3->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}
















