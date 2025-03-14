#ifndef __UART1_H__
#define __UART1_H__

// STM32外设库头文件
#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>   
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "Delay.h"
#include <string.h>


extern QueueHandle_t queue;
//extern char buf[20];
//extern int size;

void USART1_Init(void);

void USART1_SendByte(uint8_t Byte);
void printf1(char *format, ...);

#endif
