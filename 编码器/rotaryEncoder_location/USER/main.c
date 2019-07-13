#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "ROTARYENCODER.h"
#include "lcd.h"

u32 counter;

int main(void)
{
	u16 currentCount = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LCD_Init();
	POINT_COLOR=RED;      //������ɫ����ɫ
	rotaryEncoder_init();
	
	while(1)
	{
 		delay_ms(1000);
		currentCount = TIM3 -> CNT;
		printf("����������ֵΪ��%d \n",currentCount+1);	   
	}
}
