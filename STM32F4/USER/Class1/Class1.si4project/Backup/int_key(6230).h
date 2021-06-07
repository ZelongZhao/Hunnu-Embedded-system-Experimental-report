#ifndef INT_KEY_H
#define INT_KEY_H

#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"

int flag_leoric ;

void key_int_init(void);
void EXTI0_IRQHandler(void);

#endif


