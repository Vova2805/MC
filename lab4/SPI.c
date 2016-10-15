#include "SPI.H"

void SPI_Initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	CS_Off();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitStruct.SPI_Direction 						= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode 								= SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize 						= SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL 								= SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA 								= SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS 									= SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler 		= SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_FirstBit 						= SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial 				= 7;
	
	SPI_Init(SPI1, &SPI_InitStruct);
	
	SPI_Cmd(SPI1, ENABLE);
}


uint8_t Write_Data(uint8_t data) 
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	SPI_I2S_SendData(SPI1, data);
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 	return SPI_I2S_ReceiveData(SPI1);
}

void Write_Reg(uint8_t addr, uint8_t data)
{
	CS_On();
	Write_Data(addr);
	Write_Data(data);
	CS_Off();
}


uint8_t Read_Reg(uint8_t addr)
{
	uint8_t data = 0;
	addr = addr | 0x80;
	CS_On();
	Write_Data(addr);
	data = Write_Data(0x00);
	CS_Off();
	return data;
}
 
void CS_On(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);
}

void CS_Off(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_3);
}

