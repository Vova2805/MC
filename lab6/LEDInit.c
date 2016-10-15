#include "LEDInit.h"

GPIO_InitTypeDef GPIO_InitStruct;

void LED_Initialize(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin 		= LED_Green | LED_Yellow | LED_Red | LED_Blue;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void LED_SwitchOnOff(LED_TypeDef led, uint8_t status)
{
	if (status != OFF)
	{
		GPIO_SetBits(GPIOD, led);
	}
	else
	{
		GPIO_ResetBits(GPIOD, led);
	}
}
