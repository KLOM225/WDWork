#ifndef __UART3_H__
#define __UART3_H__

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

void USART3_Init(void);
void USART3_SendByte(uint8_t Byte);
//void USART3_SendString(char *str);
void printf3(char *format, ...);

#endif
