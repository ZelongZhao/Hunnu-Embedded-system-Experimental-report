#include "usart.h"

extern uint16_t id;
void usart_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef p;
	p.GPIO_Mode = GPIO_Mode_AF;
	p.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	p.GPIO_PuPd = GPIO_PuPd_NOPULL;
	p.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, & p);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_USART1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	USART_InitTypeDef u;
	u.USART_BaudRate = 115200;
	u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	u.USART_Parity = USART_Parity_No;
	u.USART_StopBits = USART_StopBits_1;
	u.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART1, &u );

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel = USART1_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 2;
	n.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&n);
	USART_Cmd(USART1, ENABLE);	
}

int fputc(int c, FILE *stream){
	USART1->SR;
	USART_SendData(USART1, c&0xff);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){};
	return(c);	
}

/* 
void USART1_IRQHandler(void){
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
					{
						while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
						id = USART_ReceiveData(USART1);
						USART_ClearITPendingBit(USART1, USART_IT_RXNE);
					}
}
*/
