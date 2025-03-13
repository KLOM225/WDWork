#ifndef __UART_H__
#define __UART_H__

// STM32外设库头文件
#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>

void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void USART1_SendByte(uint8_t Byte);
void USART2_SendByte(uint8_t Byte);
void USART3_SendByte(uint8_t Byte);
void printf1(char *format, ...);

#endif
