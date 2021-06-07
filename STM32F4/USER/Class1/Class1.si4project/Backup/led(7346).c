#include "led.h"

void led_init(void){
	//RCC_AHB1ClockGatingCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitTypeDef p;
	p.GPIO_Mode = GPIO_Mode_OUT;
	p.GPIO_OType = GPIO_OType_PP;
	p.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_13;
	p.GPIO_Speed = GPIO_Speed_50MHz;
	p.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &p);
	p.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOE , &p);
}