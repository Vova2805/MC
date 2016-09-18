#include "init.h"

//----------------------------------------------
//
//----------------------------------------------
void LEDs_init_cmsis(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;
}

//----------------------------------------------
//
//----------------------------------------------
void LEDs_init_spl(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Init_LED);
}


