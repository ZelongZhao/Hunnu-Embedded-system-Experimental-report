#ifndef INT_KEY_H
#define INT_KEY_H

#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"



void key_int_init(void);
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);




#endif


