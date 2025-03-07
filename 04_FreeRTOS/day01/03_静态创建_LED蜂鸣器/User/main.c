#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// 给Idle任务开辟空间
StackType_t idle_puxStackBuffer[configMINIMAL_STACK_SIZE];// 任务栈
StaticTask_t idle_pxTaskBuffer;// TCB
// 起始任务
StackType_t puxStackBuffer[configMINIMAL_STACK_SIZE];// 任务栈
StaticTask_t pxTaskBuffer;// TCB
// 任务1
StackType_t puxStackBuffer1[configMINIMAL_STACK_SIZE];// 任务栈
StaticTask_t pxTaskBuffer1;// TCB
// 任务2
StackType_t puxStackBuffer2[configMINIMAL_STACK_SIZE];// 任务栈
StaticTask_t pxTaskBuffer2;// TCB

// 给Idle任务配置内存
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                  StackType_t ** ppxIdleTaskStackBuffer,
                                  configSTACK_DEPTH_TYPE * puxIdleTaskStackSize )
{

		*ppxIdleTaskTCBBuffer = &idle_pxTaskBuffer;
		*ppxIdleTaskStackBuffer = idle_puxStackBuffer;
		*puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


void task1 ( void * arg ){	
	// 控制PB1的Led显示
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin = GPIO_Pin_1 ;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &initType);
	
	while(1){
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		vTaskDelay(1000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		vTaskDelay(1000);
	}
}
void task2 ( void * arg ){
	// 控制PA2的Led显示
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin =  GPIO_Pin_2;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &initType);
	
	while (1) {
		// 延迟关闭与打开，实现滴滴滴
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        vTaskDelay(1000);
		
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
        vTaskDelay(1000);
    }  
}

void beginTask ( void * arg ){
	
	TaskHandle_t hand1 = xTaskCreateStatic(task1, 
									"task1",
									configMINIMAL_STACK_SIZE,
									NULL,
									4, 
									puxStackBuffer1,
									&pxTaskBuffer1 );
	
	TaskHandle_t hand2 = xTaskCreateStatic(task2, 
									"task2",
									configMINIMAL_STACK_SIZE,
									NULL,
									4, 
									puxStackBuffer2,
									&pxTaskBuffer2 );
	
	while (1) {
		
    }  
}

int main(void){
	USART1_Init();

	TaskHandle_t hand = xTaskCreateStatic(beginTask, 
									"beginTask",
									configMINIMAL_STACK_SIZE,
									NULL,
									4, 
									puxStackBuffer,
									&pxTaskBuffer );
	
	vTaskStartScheduler();
 	while(1){
	}
}
