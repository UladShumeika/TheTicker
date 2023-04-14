/**
  ******************************************************************************
  * @file    ush_stm32f4xx_uart.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    21-February-2023
  * @brief	 This file contains the implementation of functions for working with UART.
  *
  * NOTE: This file is not a full-fledged UART driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_gpio.h"
#include "ush_stm32f4xx_dma.h"
#include "ush_stm32f4xx_uart.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define PREEMPTION_PRIORITY_RX		(5U)
#define SUBPRIORITY_RX				(0)

#define PREEMPTION_PRIORITY_TX		(5U)
#define SUBPRIORITY_TX				(0)

//---------------------------------------------------------------------------
// Private variables
//---------------------------------------------------------------------------
USH_DMA_initTypeDef initDMA_txStructure = {0};
USH_DMA_initTypeDef initDMA_rxStructure = {0};

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

	uint16_t tmpReg = 0;
	uint32_t pclk = 0;

	// Check parameters
	assert_param(IS_USART_ALL_INSTANCE(initStructure->USARTx));
	assert_param(IS_USART_PINSPACK(initStructure->PinsPack));
	assert_param(IS_USART_BAUDRATE(initStructure->BaudRate));
	assert_param(IS_USART_MODE(initStructure->Mode));

	USH_USART_DISABLE(initStructure->USARTx);

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
				initGpioStructure.Pin		= (GPIO_PIN_9 | GPIO_PIN_10);

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
				initGpioStructure.Pin		= (GPIO_PIN_6 | GPIO_PIN_7);

			} else if(initStructure->Mode == USART_MODE_RX)
			{
				initGpioStructure.Pin		= GPIO_PIN_7;

			} else					// TX mode selected
			{
				initGpioStructure.Pin		= GPIO_PIN_6;
			}
		}

		GPIO_init(&initGpioStructure);
	}

	//TODO "There are only GPIO settings for USART1 pinsPack1 and pinsPack2"

	/* ----------------------- DMA configuration --------------------------- */

	if(initStructure->USARTx == USART1)
	{
		// Enable DMA2 clock
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

		// Check TX or TX/RX mode
		if(initStructure->Mode == USART_MODE_TX || initStructure->Mode == USART_MODE_RX_TX)
		{
			// DMA interrupt init
			MISC_NVIC_SetPriority(DMA2_Stream7_IRQn, PREEMPTION_PRIORITY_TX, SUBPRIORITY_TX);
			MISC_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

			initDMA_txStructure.DMAy_Streamx  			= DMA2_Stream7;
			initDMA_txStructure.Channel 				= DMA_CHANNEL_4;
			initDMA_txStructure.Direction 				= DMA_MEMORY_TO_PERIPH;
			initDMA_txStructure.PeriphInc 				= DMA_PINC_DISABLE;
			initDMA_txStructure.MemInc 			  		= DMA_MINC_ENABLE;
			initDMA_txStructure.PeriphDataAlignment 	= DMA_PERIPH_SIZE_BYTE;
			initDMA_txStructure.MemDataAlignment    	= DMA_MEMORY_SIZE_BYTE;
			initDMA_txStructure.Mode 				 	= DMA_NORMAL_MODE;
			initDMA_txStructure.Priority 			 	= DMA_PRIORITY_LOW;
			initDMA_txStructure.FIFOMode 			 	= DMA_FIFO_MODE_DISABLE;
			DMA_init(&initDMA_txStructure);
		}

		// Check RX or TX/RX mode
		if(initStructure->Mode == USART_MODE_RX || initStructure->Mode == USART_MODE_RX_TX)
		{
			// DMA interrupt init
			MISC_NVIC_SetPriority(DMA2_Stream2_IRQn, PREEMPTION_PRIORITY_TX, SUBPRIORITY_TX);
			MISC_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

			initDMA_rxStructure.DMAy_Streamx			= DMA2_Stream2;
			initDMA_rxStructure.Channel 				= DMA_CHANNEL_4;
			initDMA_rxStructure.Direction 				= DMA_PERIPH_TO_MEMORY;
			initDMA_rxStructure.PeriphInc 				= DMA_PINC_DISABLE;
			initDMA_rxStructure.MemInc 			  		= DMA_MINC_ENABLE;
			initDMA_rxStructure.PeriphDataAlignment 	= DMA_PERIPH_SIZE_BYTE;
			initDMA_rxStructure.MemDataAlignment    	= DMA_MEMORY_SIZE_BYTE;
			initDMA_rxStructure.Mode 				 	= DMA_CIRCULAR_MODE;
			initDMA_rxStructure.Priority 			 	= DMA_PRIORITY_LOW;
			initDMA_rxStructure.FIFOMode 			 	= DMA_FIFO_MODE_DISABLE;
			DMA_init(&initDMA_rxStructure);
		}
	}
		//TODO "There are only DMA settings for USART1"

}
