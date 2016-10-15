#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include "stm32f4xx_adc.h"
#include "stm32f4xx.h"  

GPIO_InitTypeDef GPIO_InitStructure;
const int green=0x1000,blue=0x8000, orange=0x2000,red=0x4000;

void init_led_port(void)									
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			
	GPIO_Init(GPIOD, &GPIO_InitStructure);					
}

void adc_init() {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef adc_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit();
	ADC_StructInit(&ADC_InitStructure);
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_CommonInit(&adc_init);
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
} 

u16 readADC1(u8 channel) {
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_3Cycles);
	ADC_SoftwareStartConv(ADC1);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

void turnOnDiods(int diod)
{
 GPIO_ResetBits(GPIOD, orange|red|green|blue);
 GPIO_SetBits(GPIOD,diod);
}

int main(void)
{
	adc_init();
	do{
	unsigned int result = readADC1(ADC_Channel_1);
	int temperature = 25; 
	//T = (Vres – 0.76)/0.0025 + 25,
	//osDelay(500000);
		if(temperature>15){
			turnOnDiods(red);
		}
		else{
		turnOnDiods(blue);
		}
	}while (1);
}
