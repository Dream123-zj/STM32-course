#include "IIC.h"
#include "delay.h"

void IIC_Init(void){

	GPIO_InitTypeDef  GPIO_InitStruct;
	//ʹ��GPIPF
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//��ʼGPIGB8 GPIGB9 
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_8 | GPIO_Pin_9; 	 //����9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT; //���
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD; //��©���
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz; //�ٶ�
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;   //����
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//��ʼ������->����״̬
	SDA_OUTPUT();
	SCL = 1;
	SDA_OUT = 1;
	
}
	

void IIC_Start(void){

	//���ģʽ
	SDA_OUTPUT();
	
	//1.���߿���
	SDA_OUT = 1;
	SCL = 1;
	delay_us(5);
	
	//2.SDA��ƽ����	H -> L
	SDA_OUT = 0;
	delay_us(5);
	
	//3.ռ��ʱ������
	SCL = 0;
	
}


void IIC_Stop(void){

	//���ģʽ
	SDA_OUTPUT();
	
	//1.ǯס����ͬʱSDAΪ��
	SDA_OUT = 0;
	SCL = 0;
	delay_us(5);
	
	//2.SCL��SDA��ƽ���� L ->	H
	SCL = 1;
	SDA_OUT = 1;
	delay_us(5);

}
		
void IIC_Write_Byte(u8 data){

	int i = 7;
	//���ģʽ
	SDA_OUTPUT();
	
	
	//һ���ֽڰ�λ��ѭ���˴�
	SCL = 0;
	for(; i >= 0; i--){
		
		SCL = 0;
		//�жϵ�ǰ����λ����λ��ǰ����λ�ں�
		if((data & (1<<i))){
		
			SDA_OUT = 1;
		}
		else{
		
			SDA_OUT = 0;
		}
		delay_us(5);	//�˴���֪��ΪʲôҪ��ʱ 1.������������
		SCL = 1;
		delay_us(5);
		
		//3.ǯס����
		SCL = 0;	
	}

	//3.ռ��ʱ�����ߣ��ͷ���������
	SCL = 0;
	SDA_OUT	= 1;
}
	
u8	IIC_Read_Byte(void){

	u8 data = 0;
	int i = 7;
	
	//����ģʽ
	SDA_INPUT();
	
	//һ���ֽڰ�λ��ѭ���˴�
	SCL = 0;
	for(; i >= 0; i--){
		
		//�͵�ƽ׼������
		delay_us(5);
		
		//�жϵ�ǰ����λ����λ��ǰ����λ�ں�
		SCL = 1;
		if(SDA_IN){
		
			data |= (1 << i);
		}
		delay_us(5);
		
		//3.ǯס����
		SCL = 0;	
	}

	//4.ռ��ʱ�����ߣ��ͷ���������
	SCL = 0;
	SDA_OUT	= 1;
	return data;
}
	
	
u8	IIC_Wait_Ack(void){

	u8 ask = 0;
	
	//����ģʽ
	SDA_INPUT();

	//1.׼��ask
	SCL = 0;
	delay_us(5);
	
	//2.��ȡASK
	SCL = 1;
	if(SDA_IN == 1){
		ask = 1;
	}
	else ask = 0;
	delay_us(5);
	
	//3.ռ��ʱ�����ߣ��ͷ���������
	SCL = 0;
	SDA_OUT	= 1;
	return ask;
	
	
}
	
void IIC_Send_Ack(void){

	//���ģʽ
	SDA_OUTPUT();
	
	//1.׼������
	SCL = 0;
	SDA_OUT = 0;
	delay_us(5);	
	
	//2.����ASK
	SCL = 1;
	delay_us(10);
	
	//3.ռ��ʱ�����ߣ��ͷ���������
	SCL = 0;
	SDA_OUT	= 1;

}
	
	
	
void IIC_Send_NAck(void){

	//���ģʽ
	SDA_OUTPUT();
	
	//1.׼������
	SCL = 0;
	SDA_OUT = 1;
	delay_us(5);	
	
	//2.����NASK
	SCL = 1;
	delay_us(5);
	
	//3.ռ��ʱ�����ߣ��ͷ���������
	SCL = 0;
	SDA_OUT	= 1;
}
