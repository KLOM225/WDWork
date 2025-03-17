#ifndef __ADC_H__
#define __ADC_H__

// STM32外设库头文件

#include <stdio.h>
#include <string.h>
#include "UART3.h"
#include "UART1.h"

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);

#endif
