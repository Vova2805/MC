#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_syscfg.h>
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

EXTI_InitTypeDef exti;										
NVIC_InitTypeDef nvic;										
GPIO_InitTypeDef GPIO_InitStructure;						

const int green=0x1000, orange=0x2000,red=0x4000,blue=0x8000;
int diods[]={green,orange,red,blue};
int DiodsCount=-1;

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

void init_EXTI()											
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			
	GPIO_Init(GPIOA, &GPIO_InitStructure);					

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

    exti.EXTI_Line = EXTI_Line0;							
    exti.EXTI_Mode = EXTI_Mode_Interrupt;					
    														
    exti.EXTI_Trigger = EXTI_Trigger_Rising;	
    exti.EXTI_LineCmd = ENABLE;								
    EXTI_Init(&exti);										

    nvic.NVIC_IRQChannel = EXTI0_IRQn;						
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);			
    nvic.NVIC_IRQChannelPreemptionPriority = 0;				
    nvic.NVIC_IRQChannelSubPriority = 0;					
    nvic.NVIC_IRQChannelCmd = ENABLE;						
    NVIC_Init(&nvic);										
}


void turnOnDiods()
{
	if(DiodsCount<4)GPIO_SetBits(GPIOD, diods[DiodsCount]);
 	else
		{
			for(int i=3;i>=0;i--)
			{	
				GPIO_ResetBits(GPIOD, diods[i]);	
			}	
			DiodsCount=-1;			
		}
}

void EXTI0_IRQHandler()
{						
	while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
	{
		osDelay(5);
	}
  osDelay(50);
	DiodsCount++;
	turnOnDiods();
	EXTI_ClearITPendingBit(EXTI_Line0);		
}

int main(void)
{
	__enable_irq();					
	init_led_port();									
	init_EXTI();
	while(1)
	{
	}
}
