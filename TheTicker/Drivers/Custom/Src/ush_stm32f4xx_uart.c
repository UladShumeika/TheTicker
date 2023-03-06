/**
  ******************************************************************************
  * @file    ush_stm32f4xx_uart.c
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
// Defines
//---------------------------------------------------------------------------
#define PREEMPTION_PRIORITY_RX		(5U)
#define SUBPRIORITY_RX				(0)

#define PREEMPTION_PRIORITY_TX		(5U)
#define SUBPRIORITY_TX				(0)

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------
#define IS_UART_BAUDRATE(BAUDRATE) ((BAUDRATE) <= 10500000U)

//---------------------------------------------------------------------------
// Private structure
//---------------------------------------------------------------------------

/**
 * @brief DMA stream and channel structure definition
 */
typedef struct
{
	DMA_Stream_TypeDef *DMAy_Streamx;	/* A pointer to Stream peripheral to be used where y is 1 or 2 and x is from 0 to 7. */

	USH_DMA_channels Channel;			/* A channel to be used for the specified stream. */

} USH_USART_streamAndChannelTypeDef;

//---------------------------------------------------------------------------
// Private variables
//---------------------------------------------------------------------------
USH_USART_streamAndChannelTypeDef streamAndChannel = {0,};

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static uint16_t USART_BRRSampling16(uint32_t pclk, uint32_t bautrate);
static uint32_t USART_getPCLK1Freq(void);
static uint32_t USART_getPCLK2Freq(void);
static void fillInInternalStructure(USART_TypeDef* usart, USH_USART_streamAndChannelTypeDef* streamAndChannel);

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

	#warning "There are only GPIO settings for USART1 pinsPack1 and pinsPack2"

	/* ----------------------- DMA configuration --------------------------- */

	if(initStructure->USARTx == USART1)
	{
		// Enable DMA2 clock
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

		// Check TX or TX/RX mode
		if(initStructure->Mode == USART_MODE_TX || initStructure->Mode == USART_MODE_RX_TX)
		{
			USH_DMA_initTypeDef initDMA_txStructure = {0,};

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
			USH_DMA_initTypeDef initDMA_rxStructure = {0,};

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
		#warning "There are only DMA settings for USART1"

	/* ----------------------- USART configuration ------------------------- */

	// Check parameters
	assert_param(IS_UART_BAUDRATE(initStructure->BaudRate));

	// Oversampling by 16, 8 data bits, parity control disabled, multiprocessor communication disabled
	if(initStructure->Mode == USART_MODE_RX_TX)
	{
		tmpReg |= USART_MODE_RX_TX;
	} else if(initStructure->Mode == USART_MODE_RX)
	{
		tmpReg |= USART_MODE_RX;
	} else
	{
		tmpReg |= USART_MODE_TX;
	}

	initStructure->USARTx->CR1 = tmpReg;

	// Synchronous mode disabled, LIN disabled, 1 stop bit
	tmpReg = 0;
	initStructure->USARTx->CR2 = tmpReg;

	// IrDA disable, half duplex mode is not selected, flow control disabled.
	tmpReg = initStructure->USARTx->CR3;
	tmpReg &= 0xC0; // clear all bits except DMAT, DMAR
	initStructure->USARTx->CR3 = tmpReg;

	// Get PCLK frequency
	if(initStructure->USARTx == USART1 || initStructure->USARTx == USART6)
	{
		pclk = USART_getPCLK2Freq();
	} else
	{
		pclk = USART_getPCLK1Freq();
	}

	// USART BRR configuration
	initStructure->USARTx->BRR = USART_BRRSampling16(pclk, initStructure->BaudRate);

	USH_USART_ENABLE(initStructure->USARTx);
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief	This function transmits data using DMA.
 * @param 	usart - A pointer to U(S)ART peripheral to be used where x is between 1 to 8.
 * @param 	data - The data to be transmitted.
 * @param 	size - The data transfer size.
 * @retval	The periphery status.
 */
USH_peripheryStatus USART_transmitDMA(USART_TypeDef* usart, uint8_t* data, uint16_t size)
{
	USH_USART_streamAndChannelTypeDef* settings = &streamAndChannel;

	// check parameters
	assert_param(IS_USART_ALL_INSTANCE(usart));
	assert_param(IS_USART_MESSAGE_SIZE(size));

	fillInInternalStructure(usart, &streamAndChannel);

	if(!(usart->SR & USART_SR_TC))
	{
		return STATUS_BUSY;
	}

	// Set data size
	settings->DMAy_Streamx->NDTR = size;

	// Set peripheral address
	settings->DMAy_Streamx->PAR = (uint32_t)&usart->DR;

	// Set memory address
	settings->DMAy_Streamx->M0AR = (uint32_t)data;

	// Clear interrupt flags
	DMA_clearFlags(settings->DMAy_Streamx, DMA_FLAG_ALL);

	// Enable interrupts
	settings->DMAy_Streamx->CR |= DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE;

	// Enable DMA stream
	DMA_state(settings->DMAy_Streamx, ENABLE);

	USART_clearFlags(usart, USART_FLAG_TC);

	// Enable U(S)ART TX DMA
	usart->CR3 |= USART_CR3_DMAT;

	return STATUS_OK;
}

/**
 * @brief 	This function clears U(S)ART flags.
 * @param 	usart - A pointer to U(S)ART peripheral to be used where x is between 1 to 8.
 * @param 	flags - U(S)ART flags. This parameter can be a value of @ref USH_USART_flags.
 * @retval	None.
 */
void USART_clearFlags(USART_TypeDef* usart, USH_USART_flags flags)
{
	// Check parameters
	assert_param(IS_USART_ALL_INSTANCE(usart));
	assert_param(IS_USART_CLEAR_FLAGS(flags));

	usart->SR = ~(flags);
}

//---------------------------------------------------------------------------
// Static Functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function calculates BRR value.
 * @note	Most of the numbers are needed in order not to use float. 50 - for rounding.
 * @param 	pclk - PCLK frequency.
 * @param 	baudrate - The desired baudrate.
 * @return	BRR value.
 */
static uint16_t USART_BRRSampling16(uint32_t pclk, uint32_t baudrate)
{
	// get usartDiv
	uint32_t usartDiv = (uint32_t)((((uint64_t)pclk) * 25U) / (((uint64_t)baudrate) * 4U));

	// get mantissa
	uint32_t mantissa = usartDiv / 100U;

	// get fraction
	uint32_t fraction = (((usartDiv - (mantissa * 100U)) * 16U) + 50U) / 100U;

	return ((uint16_t)(mantissa << 4U) | fraction);
}

/**
 * @brief	This function returns PCLK1 frequency.
 * @param	None.
 * @retval	PCLK1 frequency.
 */
static uint32_t USART_getPCLK1Freq(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> 10]); // 10 - a position in CFGR register
}

/**
 * @brief	This function returns PCLK2 frequency.
 * @param	None.
 * @retval	PCLK2 frequency.
 */
static uint32_t USART_getPCLK2Freq(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> 13]); // 13 - a position in CFGR register
}

/**
 * @brief 	This function populates an internal structure that contains the actual stream and channel
 * 			the selected U(S)ART.
 * @param 	usart - A pointer to U(S)ART peripheral to be used where x is between 1 to 8.
 * @param	streamAndChannel - A pointer to the internal structure.
 * @retval	None.
 */
static void fillInInternalStructure(USART_TypeDef* usart, USH_USART_streamAndChannelTypeDef* streamAndChannel)
{
	if(usart == USART1)
		{
			streamAndChannel->DMAy_Streamx 		= DMA2_Stream7;
			streamAndChannel->Channel			= DMA_CHANNEL_4;

		} else if(usart == USART2)
			   {
					streamAndChannel->DMAy_Streamx 		= DMA1_Stream6;
					streamAndChannel->Channel			= DMA_CHANNEL_4;

			   } else if(usart == USART3)
			   	      {
				   	   	   streamAndChannel->DMAy_Streamx 		= DMA1_Stream3;
				   	   	   streamAndChannel->Channel			= DMA_CHANNEL_4;

			          } else if(usart == UART4)
			                 {
			        	  	  	  streamAndChannel->DMAy_Streamx	= DMA1_Stream4;
			        	  	  	  streamAndChannel->Channel			= DMA_CHANNEL_4;

			                 } else if(usart == UART5)
			                 {
			                	 streamAndChannel->DMAy_Streamx 	= DMA1_Stream7;
			                	 streamAndChannel->Channel			= DMA_CHANNEL_4;

			                 } else if(usart == USART6)
			                 	 	{
			                	 	 	 streamAndChannel->DMAy_Streamx 	= DMA2_Stream6;
			                	 	 	 streamAndChannel->Channel			= DMA_CHANNEL_5;

			                 	 	} else if(usart == UART7)
			                 	 	       {
			                 	 				streamAndChannel->DMAy_Streamx 	= DMA1_Stream1;
			                 	 				streamAndChannel->Channel		= DMA_CHANNEL_5;

			                 	 	       } else		// UART8
			                 	 	       {
			                 	 	    	   streamAndChannel->DMAy_Streamx 	= DMA1_Stream0;
			                 	 	    	   streamAndChannel->Channel		= DMA_CHANNEL_5;
			                 	 	       }
}
