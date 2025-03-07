#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

void task1 ( void * arg ){	
	// 控制PB1的Led显示
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin = GPIO_Pin_1 ;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &initType);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	vTaskDelay(1000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	while(1){
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
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	vTaskDelay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	while(1){
		//vTaskDelay(1000);
	}
}


void printTaskInfo(TaskHandle_t taskHandle)
{
TaskStatus_t xTaskDetails;

// 获取任务信息
vTaskGetInfo(taskHandle, &xTaskDetails, pdTRUE, eInvalid);

// 打印任务信息
printf1("Task Name: %s\n", xTaskDetails.pcTaskName);
printf1("Task Priority: %d\n", xTaskDetails.uxCurrentPriority);
printf1("Base Priority: %d\n", xTaskDetails.uxBasePriority);
printf1("Task State: %d\n", xTaskDetails.eCurrentState);
printf1("Stack Base Address: %p\n", xTaskDetails.pxStackBase);
printf1("Stack High Water Mark: %d\n", xTaskDetails.usStackHighWaterMark);
printf1("Task Run Time: %d ticks\n", xTaskDetails.ulRunTimeCounter);
}

void beginTask(void * arg){
	TaskHandle_t taskinfo1, taskinfo2;
	
	xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 3, &taskinfo1);
	xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 3, &taskinfo2);
 	
	
	
	printTaskInfo(taskinfo1);
	printTaskInfo(taskinfo2);
	
	while(1){
		
	}
	
}
int main(void){
	USART1_Init();
	
	xTaskCreate(beginTask, "beginTask", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	
	vTaskStartScheduler();
	
	while(1){
		}
}
