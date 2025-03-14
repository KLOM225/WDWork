#ifndef __UART2_H__
#define __UART2_H__

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

void USART2_Init(void);
void USART2_SendByte(uint8_t Byte);
void printf2(char *format, ...);

#endif
