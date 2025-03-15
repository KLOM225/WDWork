#include "UART1.h"

void USART1_Init(void){  //串口
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	// 初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//PA9:USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10:USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// USART1配置
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);	

	// 配置接收中断 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 12;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 启动USART1
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		char data = USART_ReceiveData(USART1);
//        printf1("****\r\n");
		
		BaseType_t stat = pdTRUE;
		xQueueSendFromISR(queue1, &data, &stat);

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
}



// 发送字节
void USART1_SendByte(uint8_t Byte) {
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

//void USART1_SendString(char *str) {
//    while (*str) {
//        USART1_SendByte((uint8_t)*str++);
//    }
//}

void printf1(char *format, ...)
{
	char strs[100];	
	va_list list;
	va_start(list, format);
	vsprintf(strs, format, list);
	va_end(list);

	for (uint8_t i=0; strs[i] != '\0'; i++){
		USART1_SendByte(strs[i]);
	}
}



