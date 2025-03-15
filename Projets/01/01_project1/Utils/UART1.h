#ifndef __UART1_H__
#define __UART1_H__


#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>   
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "Delay.h"
#include <string.h>

extern QueueHandle_t queue1,queue2,queue3;

void USART1_Init(void);
void USART1_SendByte(uint8_t Byte);
//void USART1_SendString(char *str);
void printf1(char *format, ...);

#endif
