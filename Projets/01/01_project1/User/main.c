#include "stm32f10x.h"   
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"  // 引入头文件
#include "UART1.h"
#include <string.h>




int main(void){
	USART1_Init();
	USART2_Init();
	USART3_Init();
	
	
	while(1){
	}
}
