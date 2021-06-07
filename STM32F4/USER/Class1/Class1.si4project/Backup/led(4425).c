#include "led.h"
void led_init(void){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitTypeDef p;
	p.GPIO_Mode = GPIO_Mode_OUT;
	p.GPIO_OType = GPIO_OType_PP;
	p.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_13;
	p.GPIO_Speed = GPIO_Speed_50MHz;
	p.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &p);
	p.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOE, &p);

	GPIO_SetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_13);
	GPIO_SetBits(GPIOF, GPIO_Pin_13|GPIO_Pin_14);
	
}

void led_one_on(LED_ID led_n){
	switch (led_n)
	{
		case LED_D1:{
			GPIO_ResetBits(GPIOF,GPIO_Pin_9);
			GPIO_SetBits(GPIOF,GPIO_Pin_10);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
			break;
		}
		case LED_D2:{
			GPIO_ResetBits(GPIOF,GPIO_Pin_10);
			GPIO_SetBits(GPIOF,GPIO_Pin_9);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
			break;
		}
		case LED_D3:{
			GPIO_ResetBits(GPIOE,GPIO_Pin_13);
			GPIO_SetBits(GPIOE,GPIO_Pin_10);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
			break;
		}
		case LED_D4:{
			GPIO_ResetBits(GPIOF,GPIO_Pin_14);
			GPIO_SetBits(GPIOF,GPIO_Pin_13);
			GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
			break;
		}
		default:
			break;
	}
}

void delay(int num){
	while(num--);
}

void led_loop(void){
	LED_ID led_n=LED_D1;
	for(led_n=LED_D1;led_n<=LED_D4;led_n++){
		led_one_on(led_n);
		delay(0x666666);
	}
}