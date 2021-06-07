#include "key.h"

void key_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef k;
	k.GPIO_Mode = GPIO_Mode_IN;
	k.GPIO_Pin = GPIO_Pin_0;
	k.GPIO_Speed = GPIO_Speed_50MHz;
	k.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &k);
	k.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOE, &k);
}
void key_check(void){
	uint8_t value_1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	uint8_t value_2=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
	if(value_1&0x01)
	{
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)&0x01);
		all_reset();
		led_loop();
	}else if(value_2&0x04){
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)&0x04);
		all_reset();
		led_loop();
	}
	
}

void all_reset(void){
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);//重置蜂鸣器
	GPIO_SetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_10);
	GPIO_SetBits(GPIOF, GPIO_Pin_13|GPIO_Pin_14);
}
