//author:ora
//email:1301912993@qq.com

#include "ROTARYENCODER.h"
#include "usart.h"


#define SAMPLE_CYCLE				500		//ms


/*
 *@brief����������ʼ���������ⲿ�жϳ�ʼ������ʱ��update�жϳ�ʼ��
 *@param��none
 *@retval:none
 */
void rotaryEncoder_init(void)
{

	
	EXTI_InitTypeDef	EXTI_InitStruct;
	NVIC_InitTypeDef 	NVIC_InitStruct;
	GPIO_InitTypeDef 	GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	int prescaler = 8400 - 1;
	int period = SAMPLE_CYCLE * 10;
	
	/****************************************EXTI8****************************/
	
	//1.ʹ��ʱ��  -->  EXIT8   --> PF8
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//2.�ж�ӳ����
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = ;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
	
	//4.��ʼ���ⲿ�ж�
	EXTI_InitStruct.EXTI_Line = EXTI_Line8;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	//5.�����ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	/********************************************TIM3*****************************/
	
	//1.ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	

	//2.��ʱ����ʼ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = period;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//3.�����ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
	//4.����ʱ�������ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	//5.ʹ��TIM
	TIM_Cmd(TIM3, ENABLE);

	

}

extern u32 counter;
/*
 *@brief���ⲿ�жϺ�����counter��һ
 *@param��none
 *@retval:none
 */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		counter ++;
		//printf("%d\n",counter);
		EXTI_ClearITPendingBit(EXTI_Line8);
		
	}


}

/*
 *@brief��TIM3�жϺ�������ӡcounter������counter
 *@param��none
 *@retval:none
 */
void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{

		printf("counter:%d, ", counter);
		counter = 0;

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}


}
