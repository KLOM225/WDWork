#include "UART1.h"
#include "UART2.h"
#include "UART3.h"
#include "Delay.h"
#include "Bluet_to_wifi.h"

#define BUF_SIZE 60

QueueHandle_t TTL_queue, Blue_queue, ESP_queue, TCP_queue;

//将串口的接收到的信息转发
void Ttl_to_wifi(void * arg) {
    char buf2[BUF_SIZE] = {0};
    int size2 = 0;
    char ch2 = 0;

    while (1) {
        BaseType_t  ret2 = xQueueReceive(TTL_queue, &ch2, 5000);

        if (ret2 == pdPASS) {
            buf2[size2] = ch2;
            size2++;
        } else {
            if (size2 > 0) {

                printf1("TTL %s \r\n", buf2); 
                // printf2("%s", buf2);		//串口接收的信息发送给蓝牙模块
                printf3("%s", buf2);   //串口接收的信息发送给wifi模块
				
                memset(buf2, 0, sizeof(buf2));
                size2 = 0;
            }
        }
    }
}

//tcp连接任务
void tcp_connect(void * arg) {
    char buf4[BUF_SIZE] = {0};
    while (1) {
		xQueueReceive(TCP_queue, buf4, 5000);
        if (strstr(buf4, "AT+CWJAP_DEF")){
			
			printf1("------\r\n");
			printf1("buf4  %s\r\n", buf4);
			printf1("------\r\n");
			wifi_to_tcp(buf4);
			printf1("buf4  %s\r\n", buf4);
			memset(buf4, 0, sizeof(buf4));
		}
    }
	
}

//将wifi(esp)接收到的信息转发到串口，打印出来
void wifi_to_ttl(void * arg) {
    char buf3[BUF_SIZE] = {0};
    int size3 = 0;
    char ch3 = 0;

    while (1) {
		// 从中断接收信息，存入buf3
        BaseType_t ret3 = xQueueReceive(ESP_queue, &ch3, 5000);
		
        if (ret3 == pdPASS) {
            buf3[size3] = ch3;
            size3++;
        } else {
            if (size3 > 0) {
				// 转发给串口，查看wifi输出的信息
                printf1("wifi %s \r\n", buf3);
				// 将信息转发给tcp连接任务
				xQueueSend(TCP_queue, buf3, 5000);
                size3 = 0;
                memset(buf3, 0, sizeof(buf3));
            }
        }
    }
}

//将蓝牙接收到的信息转发给串口
// 当蓝牙收到连接信息时，信息转发给wifi模块，并发给串口
void Bluetooth_to_ttl(void * arg) {
    char buf[BUF_SIZE] = {0};
    int size = 0;
    char ch = 0;
    char AT_wifi[64] = {0};
	
    while (1) {
        BaseType_t  ret = xQueueReceive(Blue_queue, &ch, 5000);

        if (ret == pdPASS) {
            buf[size] = ch;
            size++;
        } else {
            if (size > 0) {
                printf1("Bluetooth: %s \r\n", buf);
				
				//AT指令转换
                int ret = convert_wifi_config(buf, AT_wifi, sizeof(AT_wifi));
				// 如果转换成功，则发送给wifi模块
                if (ret == 0) {
                    printf1("%s\r\n", AT_wifi);
                    printf3("%s\r\n", AT_wifi);
                }
				
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

    TTL_queue = xQueueCreate(50, 1);
    Blue_queue = xQueueCreate(50, 1);
    ESP_queue = xQueueCreate(50, 1);
	TCP_queue = xQueueCreate(2, 60);
    
	xTaskCreate(Bluetooth_to_ttl, "Bluetooth_to_ttl", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(Ttl_to_wifi, "Ttl_to_wifi", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(wifi_to_ttl, "wifi_to_ttl", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tcp_connect, "tcp_connect", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

    vTaskStartScheduler();

    while (1) {

    }
}
