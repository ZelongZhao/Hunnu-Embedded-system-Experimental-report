#include "int_key.h"
void key_int_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef k;
	k.GPIO_Mode = GPIO_Mode_IN;
	k.GPIO_Pin = GPIO_Pin_0;
	k.GPIO_Speed = GPIO_Speed_50MHz;
	k.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &k);
	k.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOE, &k);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA,  EXTI_PinSource0);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource2);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource3);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource4);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);

	EXTI_InitTypeDef e;
	e.EXTI_Line = EXTI_Line0|EXTI_Line2|EXTI_Line3|EXTI_Line4;
	e.EXTI_LineCmd = ENABLE;
	e.EXTI_Mode = EXTI_Mode_Interrupt;
	e.EXTI_Trigger = EXTI_Trigger_Rising_Falling;

	EXTI_Init(&e);
}

