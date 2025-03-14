#ifndef __UART3_H__
#define __UART3_H__

#include "UART1.h"

extern QueueHandle_t queue1,queue2,queue3;

void USART3_Init(void);
void USART3_SendByte(uint8_t Byte);
void USART3_SendString(char *str);
void printf3(char *format, ...);

#endif
