#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

void SPI_Initialize(void);
void CS_On(void);
void CS_Off(void);
void Write_Reg(uint8_t addr, uint8_t data);
uint8_t Read_Reg(uint8_t addr);

#endif
