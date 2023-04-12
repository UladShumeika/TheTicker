/**
  ******************************************************************************
  * @file    custom_stm32f429_spi.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    16-January-2023
  * @brief   This file contains all the functions prototypes for the SPI firmware
  *          library.
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "custom_stm32f429_spi.h"

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

static void SPI_gpioInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

#ifdef USE_SPI1
	if(GPIOx == SPI1)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin;
		GPIO_InitStruct.GPIO_Mode			= GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed 			= GPIO_High_Speed;
		GPIO_InitStruct.GPIO_OType 			= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd			= GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
#endif



}

