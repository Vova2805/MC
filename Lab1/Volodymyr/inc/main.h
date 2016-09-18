#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "init.h"

#define	LED_CMSIS()			led_CMSIS()
#define	LED_SPL()			 	led_SPL()

#define	YELLOW_ON()			GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define	YELLOW_OFF()		GPIO_ResetBits(GPIOD, GPIO_Pin_13)
#define	RED_ON()				GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define	RED_OFF()				GPIO_ResetBits(GPIOD, GPIO_Pin_14)

#define LED_GREEN				0x1000
#define LED_YELLOW			0x2000
#define LED_RED					0x4000
#define LED_BLUE				0x8000

void led_CMSIS(void);
void led_SPL(void);

#endif
