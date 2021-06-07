#include "systick.h"

#define rSysTickCtrl *((volatile unsigned long *)0xE00E010)
#define rSysTickLoad *((volatile unsigned long *)0xE00E014)
#define rSysTickVal *((volatile unsigned long *)0xE00E018)

uint32_t cnt = 0;

void SysTick_Handler(void)
{
	if(cnt != 0){
		cnt--;
	}
}

void Delay_ms(uint32_t d){

	SysTick_Config(SystemCoreClock /1000);	cnt = d;
	while (cnt!=0);
	rSysTickCtrl &=  ~(1 << 0) ; // bit0 -> 0 disable systick
}

void Delay_us(uint32_t d){

	SysTick_Config(SystemCoreClock/1000000);	cnt = d;
	while (cnt!=0);
	rSysTickCtrl &=  ~(1 << 0) ; // bit0 -> 0 disable systick

}

