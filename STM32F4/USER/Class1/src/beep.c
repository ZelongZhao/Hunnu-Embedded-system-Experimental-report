#include "beep.h"
int note[] = {M3,M2,M4,M3,M1,M5,M7, H1,M7,M1,M1,M1,M6,M6, ZERO,M6,M5,M5,M5,M4,M3,
M2,M3,M4,M3,M3, M3,L4,L5,M3,M4,M5,M7,  
H2,M7,H1,H1,ZERO,H1,
H1,M5,M5,M6,M5,M4,M4,M2,M3,
M4,M5,M6,M1,M6,M7,M7}  ;
float rhythm[]= {0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5,0.5,0.5,2,0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5,0.5,0.25,0.25,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.75,0.25,1};
	int flag = 0;
int length = sizeof(note)/sizeof(note[0]);
void beep_init(int f){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);

	GPIO_InitTypeDef b;
	b.GPIO_Mode = GPIO_Mode_AF;
	b.GPIO_Pin = GPIO_Pin_8;
	b.GPIO_OType = GPIO_OType_PP;
	b.GPIO_Speed = GPIO_Speed_50MHz;
	b.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOF, &b);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);

//tim13-timebase
	TIM_TimeBaseInitTypeDef t;
	t.TIM_CounterMode = TIM_CounterMode_Down;
	t.TIM_Prescaler = 8399;
	t.TIM_Period = f;
	TIM_TimeBaseInit(TIM13, &t);

//tim13-
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = TIM_OCMode_PWM2;
	oc.TIM_Pulse = f*0.6;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM13, &oc);
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM13,ENABLE);
	TIM_Cmd( TIM13,ENABLE);
} 
void beep_on(void){
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
}

void music_on(void){
	int x;
	for(x=0; x<length;x++){
		if(flag == 1){
			flag = 0;
		}
		if (note[x] == ZERO){
			RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM13, DISABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);
			flag = 1;
		}
		beep_init(note[x]);
		if(flag == 1){
			Delay_ms((uint32_t )(800*rhythm[x]));
			flag = 0;
		}
		else Delay_ms((uint32_t )(600*rhythm[x]));
	}
	RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM13, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);
}
