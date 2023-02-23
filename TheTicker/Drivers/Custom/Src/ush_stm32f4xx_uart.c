/**
  ******************************************************************************
  * @file    ush_stm32f4xx_uart.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    21-February-2023
  * @brief	 This file contains the implementation of functions for working with UART
  *
  * NOTE: This file is not a full-fledged UART driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_uart.h"
#include "ush_gpio.h"
#include "ush_dma.h"

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes the U(S)ART peripheral according to the specified parameters in the USH_USART_initTypeDef.
 * @note 	This function has default settings:
 *			- Asynchronous mode;
 *			- Word Length - 8 bits;
 *			- Parity - None;
 *			- Stop bits - 1;
 *			- Hardware flow control - None;
 *			- Over sampling - 16 samples.
 * @param 	initStructure - A pointer to a USH_USART_initTypeDef structure that contains the configuration information
 * 							for the specified U(S)ART peripheral.
 * @retval	None.
 */
void USART_init(USH_USART_initTypeDef *initStructure)
{
	USH_GPIO_initTypeDef initGpioStructure = {0,};

	uint32_t temp_rgr;

	/* ----------------------- GPIO configuration -------------------------- */

	// Fill in the initGpioStructure to initialize the GPIO pins, these parameters are used for all pinsPacks
	initGpioStructure.Mode			= GPIO_MODE_ALTERNATE_PP;
	initGpioStructure.Pull			= GPIO_PULLUP;
	initGpioStructure.Speed			= GPIO_SPEED_VERY_HIGH;

	if(initStructure->USARTx == USART1)
	{
		// USART1 clock enable
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		if(initStructure->PinsPack == USART_PINSPACK_1) 	// Pins configuration according to pinsPack_1
		{
			// GPIOA clock enable
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

			// USART1 GPIO pins pack 1 configuration
			// PA9 	   ------> USART1_TX
			// PA10    ------> USART1_RX
			initGpioStructure.GPIOx 		= GPIOA;
			initGpioStructure.Alternate		= GPIO_AF7_USART1;

			if(initStructure->Mode == USART_MODE_RX_TX)
			{
				initGpioStructure.Pin		= (GPIO_PIN_9 || GPIO_PIN_10);

			} else if(initStructure->Mode == USART_MODE_RX)
			{
				initGpioStructure.Pin		= GPIO_PIN_10;

			} else					// TX mode selected
			{
				initGpioStructure.Pin		= GPIO_PIN_9;
			}

		} else												// Pins configuration according to pinsPack_2
		{
			// GPIOB clock enable
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

			// USART1 GPIO pins pack 1 configuration
			// PB6 	   ------> USART1_TX
			// PB7     ------> USART1_RX
			initGpioStructure.GPIOx 		= GPIOB;
			initGpioStructure.Alternate		= GPIO_AF7_USART1;

			if(initStructure->Mode == USART_MODE_RX_TX)
			{
				initGpioStructure.Pin		= (GPIO_PIN_6 || GPIO_PIN_7);

			} else if(initStructure->Mode == USART_MODE_RX)
			{
				initGpioStructure.Pin		= GPIO_PIN_7;

			} else					// TX mode selected
			{
				initGpioStructure.Pin		= GPIO_PIN_6;
			}
		}

		GPIO_init(&initGpioStructure);

	} else
	{
		// not implemented for other modules
	}

	/* ----------------------- DMA configuration --------------------------- */
	/* ----------------------- USART configuration ------------------------- */
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------
