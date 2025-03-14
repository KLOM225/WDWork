#ifndef __UART2_H__
#define __UART2_H__

#include "UART1.h"


extern QueueHandle_t queue1,queue2,queue3;

void USART2_Init(void);
void USART2_SendByte(uint8_t Byte);
void USART2_SendString(char *str);
void printf2(char *format, ...);

#endif
