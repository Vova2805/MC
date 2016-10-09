#include "leds.h" 

void init_leds(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GREEN|ORANGE|RED|BLUE;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
}

void LEDSwitchOnOff(LED_COLOURS color, SWITCH colorSwitch){
	if(colorSwitch == ON){
		GPIO_SetBits(GPIOD, color);
	}
	else{
		GPIO_ResetBits(GPIOD, color);
	}
}

void turnOffAll(void){
	LEDSwitchOnOff(RED,OFF);
	LEDSwitchOnOff(BLUE,OFF);
	LEDSwitchOnOff(GREEN,OFF);
	LEDSwitchOnOff(ORANGE,OFF);
}



