#include "main.h"

uint16_t delay_count=0;
void led_CMSIS(void);
void led_SPL(void);
void SysTick_Handler(void);
void delay_ms(uint16_t delay_temp);

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);//1 ms
	led_CMSIS();
	//led_SPL();
}

//----------------------------------------------
//
//----------------------------------------------
void led_CMSIS(void){
	LEDs_init_cmsis();
	uint32_t i = 0;
	while(1)
	{
		i = i + 500;
		GPIOD->ODR |= LED_RED|LED_YELLOW;
		delay_ms(i);
		GPIOD->ODR |= 0x0000;
		delay_ms(i);
	}
}

//----------------------------------------------
//
//----------------------------------------------
void led_SPL(void){
	LEDs_init_spl();
	uint32_t i = 0;
	while(1)
	{
		i = i + 500;
		RED_ON();
		YELLOW_ON();
		delay_ms(i);
		RED_OFF();
		YELLOW_OFF();
		delay_ms(i);
	}
}

//----------------------------------------------
//
//----------------------------------------------
void SysTick_Handler(void)//1ms
{
	if (delay_count > 0)
	{
		delay_count--;
	}
}

//----------------------------------------------
//
//----------------------------------------------
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	while(delay_count){}
}