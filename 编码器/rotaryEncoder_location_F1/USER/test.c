#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "timer.h"	 	 
	  
int main(void)
{			
 	u16 currentCount;
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	Encoder_Init();

   	while(1)
	{
 		delay_ms(1000);
		currentCount = TIM3 -> CNT;
		printf("����������ֵΪ��%d \n",currentCount+1);	   
	}	 
}

























