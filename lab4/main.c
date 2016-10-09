#include "SPI.h"
#include "cmsis_os.h"
#include "stm32f4xx_adc.h"
uint16_t Out_X = 0x0;
uint16_t Out_Y = 0x0;
uint16_t Out_Z = 0x0;


int main(void)
{
	SPI_Initialize();

	Write_Reg(0x20, 0x9F);
	
	while(1)
	{
		Out_X = ((uint16_t)Read_Reg(0x29) << 8) | ((uint16_t)Read_Reg(0x28));
		Out_Y = ((uint16_t)Read_Reg(0x2B) << 8) | ((uint16_t)Read_Reg(0x2A));
		Out_Z = ((uint16_t)Read_Reg(0x2D) << 8) | ((uint16_t)Read_Reg(0x2C)); 
	}
}
