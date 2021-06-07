#include "systick.h"

#define rSysTickCtrl *((volatile unsigned long *)0xE00E010)
#define rSysTickLoad *((volatile unsigned long *)0xE00E014)
#define rSysTickVal *((volatile unsigned long *)0xE00E018)
#define systickCoreNum 1680000000

uint32_t cnt = 0;

/*
void systick_cfg(){
	rSysTickCtrl = 0;

	rSysTickLoad = 167999;
	rSysTickVal = 0;
}*/

void SysTick_Handler(void)
{
	if(cnt != 0){
		cnt--;
	}
}

void Delay_ms(uint32_t d){
	cnt = d;
	SysTick_Config(systickCoreNum/1000);
	while (cnt!=0);
	rSysTickCtrl &=  ~(1 << 0) ; // bit0 -> 0 disable systick
}

void Delay_us(uint32_t d){
	cnt = d;
	SysTick_Config(systickCoreNum/1000000);
	while (cnt!=0);
	rSysTickCtrl &=  ~(1 << 0) ; // bit0 -> 0 disable systick

}

