#include "key.h"

void key_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef k;
	k.GPIO_Mode = GPIO_Mode_IN;
	k.GPIO_Pin = GPIO_Pin_0;
	k.GPIO_Speed = GPIO_Speed_50MHz;
	k.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &k);
}