#include "UART1.h"
#include "UART2.h"
#include "UART3.h"
#include "Delay.h"
#include "Bluet_to_wifi.h"

#define BUF_SIZE 60

QueueHandle_t queue1,queue2,queue3;

//void USARTx_SendByte(USART_TypeDef* USARTx, uint8_t Byte){
//	USART_SendData(USARTx, Byte);
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
//}

//void USARTx_SendString(USART_TypeDef* USARTx,const char *str) {
//    while (*str) {
//		USARTx_SendByte(USARTx, (uint8_t)*str++);
//    }
//}

//void stm32_to_usart(USART_TypeDef* USARTx, const char *cmd){
//	char buf[BUF_SIZE] = {0};
//	snprintf(buf, BUF_SIZE, "%s\r\n", cmd);
//	USARTx_SendString(USARTx, cmd);
//}

void Ttl_to_wifi(void * arg) {
    char buf2[BUF_SIZE] = {0};
    int size2 = 0;
    char ch2 = 0;
    while (1) {
        BaseType_t  ret2 = xQueueReceive(queue1, &ch2, 1000);
        if (ret2 == pdPASS) {
            buf2[size2] = ch2;
            size2++;
        } else {
            if (size2 > 0) {
				
				printf1("%s", buf2);
				vTaskDelay(1000);
//				printf2("%s", buf2);
//				vTaskDelay(1000);
				printf3("%s", buf2); 
                memset(buf2, 0, sizeof(buf2));
                size2 = 0;
            }
        }
    }
}

void wifi_to_ttl(void * arg) {
    char buf3[BUF_SIZE] = {0};
    int size3 = 0;
   
    while (1) {
		 char ch3 = 0;
		
        BaseType_t  ret3 = xQueueReceive(queue3, &ch3, 1000);
        if (ret3 == pdPASS) {
            buf3[size3] = ch3;
            size3++;
        } else {
            if (size3 > 0) {	
                printf1("wifi %s \r\n", buf3);
				size3 = 0;
				memset(buf3, 0, sizeof(buf3));
            }
        }	
    }
}

void Bluetooth_to_ttl(void * arg) {
    char buf[BUF_SIZE] = {0};
    int size = 0;
    char ch = 0;
	char AT_wifi[64] = {0};
    while (1) {
        BaseType_t  ret = xQueueReceive(queue2, &ch, 1000);
        if (ret == pdPASS) {
            buf[size] = ch;
            size++;
        } else {
            if (size > 0) {
                printf1("Bluetooth: %s \r\n", buf);
				
				int ret = convert_wifi_config(buf, AT_wifi, sizeof(AT_wifi));
                if ( ret == 0) {
                    printf1("%s\r\n", AT_wifi); 
					printf3("%s\r\n", AT_wifi);
                }
//                if (ret == -1) {
//                    printf1("Error: Invalid input format\r\n");
//                }
//                if (ret == -2) {
//                    printf1("Error: Output buffer too small\r\n");
//                }
//				
                memset(buf, 0, sizeof(buf));
                size = 0;
            }
        }
    }
}



int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART1_Init();
    USART2_Init();
	USART3_Init();
    Delay_Init();

    queue1 = xQueueCreate(50, 1);
	queue2 = xQueueCreate(50, 1);
	queue3 = xQueueCreate(50, 1);
	
    xTaskCreate(Bluetooth_to_ttl, "Bluetooth_to_ttl", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(Ttl_to_wifi, "Ttl_to_wifi", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(wifi_to_ttl, "wifi_to_ttl", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    vTaskStartScheduler();

    while (1) {

    }
}
