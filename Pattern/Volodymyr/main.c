#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


/**///////////////////////////////////////////////////////////////////////////////////////////////////**/
int main (void){
	//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//
	GPIO_Init( GPIOD, &GPIO_InitStructure); //C
	
int green=0x1000, orange=0x2000,red=0x4000,blue=0x8000;
int diods[]={blue,orange,green,red};	
	
	while(1)
	{
		for(int i=0;i<4;i++)
   	{
		GPIO_SetBits(GPIOD, diods[i]);
	}
		
	for(int i=3;i>=0;i--)
	{	
	GPIO_ResetBits(GPIOD, diods[i]);
	}	
	}
}

