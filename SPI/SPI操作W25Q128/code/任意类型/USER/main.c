#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "spi.h"
#include "w25qxx.h"
#include "key.h"  


//ALIENTEK ̽����STM32F407������ ʵ��25
//SPIͨ�Žӿ�ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
 
 
 
//Ҫд�뵽W25Q16���ַ�������
const u8 TEXT_Buffer[]={"Explorer STM32F4 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
	
int main(void)
{ 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);     //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	//LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ�� 
	//KEY_Init(); 				//������ʼ��  
	W25QXX_Init();			//W25QXX��ʼ��
 	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"SPI TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	LCD_ShowString(30,130,200,16,16,"KEY1:Write  KEY0:Read");	//��ʾ��ʾ��Ϣ		
	while(W25QXX_ReadID()!=W25Q128)								//��ⲻ��W25Q128
	{
		LCD_ShowString(30,150,200,16,16,"W25Q128 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
		LED0=!LED0;		//DS0��˸
	}
	LCD_ShowString(30,150,200,16,16,"W25Q128 Ready!"); 
	FLASH_SIZE=16*1024*1024;	//FLASH ��СΪ16�ֽ�
  	POINT_COLOR=BLUE;			//��������Ϊ��ɫ	  
	//while(1)
	{
		
		
		
		//д������
		{
			char num_char = 'a';
			int num_int = 100;
			float num_float = -1.456;
			
			W25QXX_Write((u8*)&num_char, 0, sizeof(char));	
			printf("FLASHд���ַ����������:%c\n", num_char);
			
			W25QXX_Write((u8*)&num_int, 10, sizeof(int));	
			printf("FLASHд�������������:%d\n", sizeof(double));
			
			W25QXX_Write((u8*)&num_float, 20, sizeof(float));	
			printf("\nFLASHд�븡�����������:%f\n\n", num_float);
		
		
		}
		delay_ms(5000);
		//��������
		{
			char num_char_out = 0;
			int num_int_out = 0;
			float num_float_out = 0.0;
			
			W25QXX_Read((u8*)&num_char_out, 0, sizeof(char));
			printf("FLASH�����ַ����������:%c\n", num_char_out);
			delay_ms(20);			//���ڲ�����ʱ���ỻ��ʧ�ܣ��������ۣ�
			
			W25QXX_Read((u8*)&num_int_out, 10, sizeof(int));
			printf("FLASH���������������:%d\n", num_int_out);
			delay_ms(20);			//���ڲ�����ʱ���ỻ��ʧ�ܣ��������ۣ�
			
			W25QXX_Read((u8*)&num_float_out, 20, sizeof(float));
			printf("FLASH���븡�����������:%f\n", num_float_out);
		} 
		
			   
	}
		while(1);
}

