#ifndef LEDINIT_H
#define LEDINIT_H

#include "stm32f4xx_conf.h"

typedef enum
{
	LED_Green 		= 	GPIO_Pin_12,
	LED_Yellow 		= 	GPIO_Pin_13,
	LED_Red 			= 	GPIO_Pin_14,
	LED_Blue 			= 	GPIO_Pin_15
}LED_TypeDef;

#define ON 1
#define OFF 0

void LED_Initialize(void);
void LED_SwitchOnOff(LED_TypeDef led, uint8_t status);

#endif
