#include "beep.h"

void beep_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitTypeDef b;
	b.GPIO_Mode = GPIO_Mode_OUT;
	b.GPIO_Pin = GPIO_Pin_13;
	b.GPIO_OType = GPIO_OType_PP;
	b.GPIO_Speed = GPIO_Speed_50MHz;
	b.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOF, &b);
} 
void beep_on(void){
	GPIO_SetBits(GPIOF,GPIO_Pin_13);
}
