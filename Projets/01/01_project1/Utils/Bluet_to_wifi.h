#ifndef __BLUE_TO_WIFI_H__
#define __BLUE_TO_WIFI_H__

// STM32外设库头文件

#include <stdio.h>
#include <string.h>
#include "UART3.h"

int convert_wifi_config(const char* input, char* output, size_t out_len);
void wifi_to_tcp(const char *buf);
void wifi_close_tcp(const char *buf);

#endif
