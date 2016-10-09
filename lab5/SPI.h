#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "cmsis_os.h"

void LCD_init();
void updateDisplay();
void clearDisplay();

#endif
