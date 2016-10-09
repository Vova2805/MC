#include "stm32f4xx.h"       
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "global.h"

void init_leds(void);
void LEDSwitchOnOff(LED_COLOURS color, SWITCH colorSwitch);	
void turnOffAll(void);

