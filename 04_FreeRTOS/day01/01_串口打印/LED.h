#ifndef __LED_H__
#define __LED_H__

// STM32外设库头文件
#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>

void LED_Init(void);
void LED_SendByte(uint8_t Byte);


#endif
