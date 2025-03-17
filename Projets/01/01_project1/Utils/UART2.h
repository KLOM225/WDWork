#ifndef __UART2_H__
#define __UART2_H__

#include "UART1.h"
#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>   
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "Delay.h"
#include <string.h>

extern QueueHandle_t TTL_queue,Blue_queue,ESP_queue;

void USART2_Init(void);
void USART2_SendByte(uint8_t Byte);
//void USART2_SendString(char *str);
void printf2(char *format, ...);

#endif
