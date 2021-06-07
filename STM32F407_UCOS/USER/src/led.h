#ifndef LED_H
#define LED_H

#include "stm32f4xx.h"
#include "includes.h"
#include "os_cfg.h"
#include "os.h"
typedef enum LED_ID_T{
		LED_D1 = 1,
		LED_D2,
		LED_D3,
		LED_D4
}LED_ID;

void led_init(void);
void delay(int num);
void ledLoop(void *p_arg);
void led_one_on(LED_ID led_n);


#endif
