#include "int_key.h"
uint8_t flag_leoric;
void key_int_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef k;
	k.GPIO_Mode = GPIO_Mode_IN;
	k.GPIO_Pin = GPIO_Pin_0;
	k.GPIO_Speed = GPIO_Speed_50MHz;
	k.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &k);
	k.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOE, &k);
	//SYSCFG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA,  EXTI_PinSource0);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource2);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource3);
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOE,  EXTI_PinSource4);

	//EXIT
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);
	EXTI_InitTypeDef e;
	e.EXTI_Line = EXTI_Line0|EXTI_Line4|EXTI_Line2;
	e.EXTI_LineCmd = ENABLE;
	e.EXTI_Mode = EXTI_Mode_Interrupt;
	e.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&e);
	e.EXTI_Line = EXTI_Line3;
	e.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&e);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef ic;
	ic.NVIC_IRQChannel = EXTI0_IRQn;
	ic.NVIC_IRQChannelCmd = ENABLE;
	ic.NVIC_IRQChannelPreemptionPriority = 2;
	ic.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&ic);

	ic.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&ic);
	ic.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&ic);
	ic.NVIC_IRQChannelPreemptionPriority = 0;
	ic.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&ic);
	flag_leoric = 0;

}

void EXTI0_IRQHandler(void){
	if (EXTI_GetFlagStatus(EXTI_Line0) == SET){
		GPIO_SetBits(GPIOF,GPIO_Pin_8);
		led_loop();
		led_loop();
		led_loop();
		EXTI_ClearFlag(EXTI_Line0);
	}
}

void EXTI2_IRQHandler(void){
		if (EXTI_GetFlagStatus(EXTI_Line2) == SET){
		if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)&0x01){
			GPIO_ResetBits(GPIOF,GPIO_Pin_9);
			GPIO_SetBits(GPIOF,GPIO_Pin_10);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
		}else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)&0x01){
			GPIO_ResetBits(GPIOF,GPIO_Pin_10);
			GPIO_SetBits(GPIOF,GPIO_Pin_9);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
		}
		EXTI_ClearFlag(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line3) == SET){
		if(flag_leoric == 0){
			GPIO_ResetBits(GPIOE,GPIO_Pin_13);
			GPIO_SetBits(GPIOE,GPIO_Pin_14);
			GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
			flag_leoric =1;
		}else if(flag_leoric ==1){
			GPIO_ResetBits(GPIOE,GPIO_Pin_14);
			GPIO_SetBits(GPIOE,GPIO_Pin_13);
			GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
			flag_leoric = 0;
		}	
		EXTI_ClearFlag(EXTI_Line3);
	}
}
void EXTI4_IRQHandler(void){
	if (EXTI_GetFlagStatus(EXTI_Line4) == SET){
		GPIO_ResetBits(GPIOF,GPIO_Pin_8);
		EXTI_ClearFlag(EXTI_Line4);
	}
}
