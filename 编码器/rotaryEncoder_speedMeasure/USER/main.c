#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "ROTARYENCODER.h"


u32 counter;

int main(void)
{
	counter = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

	rotaryEncoder_init();
	while(1);
	{
		
	}
}
