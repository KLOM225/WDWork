#include "UART1.h"
#include "Delay.h"
#include "UART2.h"

#define BUF_SIZE 32
QueueHandle_t queue;

void Bluetooth_rceive ( void * arg ){	

	char buf[BUF_SIZE] = {0};
	int size = 0;
	char ch = 0;
	while(1){
		BaseType_t  ret = xQueueReceive(queue, &ch, 5000);
		if(ret == pdPASS){
			buf[size] = ch;
			size++;
		}else{
			if(size > 0){
				printf1("buf: %s \r\n", buf);
				memset(buf, 0, sizeof(buf));
				size = 0;
			}
		}
		
	}
}

int main(void){
	USART1_Init();
	USART2_Init();
	Delay_Init();
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	queue = xQueueCreate(10, 1);
	
	xTaskCreate(Bluetooth_rceive, "Bluetooth_rceive", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
	
	while(1){

	}
}
