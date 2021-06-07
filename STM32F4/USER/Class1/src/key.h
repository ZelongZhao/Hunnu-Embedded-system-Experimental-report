#ifndef KEY_H
#define KEY_H

#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"
void key_init(void);
void key_check(void);
void all_reset(void);

#endif

