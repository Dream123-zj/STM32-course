#ifndef _at24c02_h_
#define _at24c02_h_

/*
*author:oraSC
*github:https://github.com/oraSC
*����������AT24C02����
*���ڣ�2019/6/26
*/

#include "stm32F4xx.h"
#include "sys.h"

void 	AT24C02_Init(void);
u8 		AT24C02_ReadOneByte(u8 addr);
void	AT24C02_ReadLenByte(u8 addr, u8 *buffer, u16 len);
void 	AT24C02_ReadLenByte_S(u8 addr, u8 *buffer, u16 len);
void 	AT24C02_WriteOneByte(u8 addr, u8 data);
void 	AT24C02_WriteLenByte(u8 addr, u8 *data, u16 len);
void 	AT24C02_WriteLenByte_S(u8 addr, u8 *data, u16 len);

#endif
