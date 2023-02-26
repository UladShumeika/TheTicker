/**
  ******************************************************************************
  * @file    ush_stm32f4xx_usart.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    21-February-2023
  * @brief   This file contains the functions prototypes for the UART firmware
  *          library.
  *
  * NOTE: This file is not a full-fledged U(S)ART driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
  */

/* The U(S)ART setting is based on the choice of a set of pins and a set of DMA.
 *
 * The set of pins.
 * 		  	  |    pinsPack_1	|    pinsPack_2   |
 * U(S)ARTx___|___TX___|___RX___|___TX___|___RX___|
 * 		      |		   |		|		 |		  |
 * USART1	  |  PA9   |  PA10  |  PB6   |  PB7   |
 * USART2	  |	 PA2   |  PA3	|  PD5   |  PD6	  |
 * USART3	  |	 PB10  |  PB11	|  PC10  |  PC11  |
 * UART4	  |	 PA0   |  PA1	|  PC10  |  PC11  |
 * UART5	  |	 PC12  |  PD2	|  ---   |  ---	  |
 * USART6	  |	 PC6   |  PC7	|  PG14  |  PG9   |
 * UART7	  |	 PE8   |  PE7   |  PF7	 |  PF6   |
 * UART8	  |  PE1   |  PE0   |  ---   |  ---   |
 *
 * The set of DMA.
 *     	      |		   dmaPack_1	    |		 dmaPack_2        |
 * U(S)ARTx___|_DMAx Stream x Channel x_|_DMAx Stream x Channel x_|
 * 		      |			                |				          |
 * USART1_TX  |      DMA2 St.7 Ch.4     |           -----         |
 * USART1_RX  |      DMA2 St.2 Ch.4     |      DMA2 St.5 Ch.4     |
 * 		      |						    |						  |
 * USART2_TX  |      DMA1 St.6 Ch.4     |			-----		  |
 * USART2_RX  |      DMA1 St.5 Ch.4     |			-----		  |
 * 		      |						    |						  |
 * USART3_TX  |      DMA1 St.3 Ch.4     |      DMA1 St.4 Ch.7     |
 * USART3_RX  |      DMA1 St.1 Ch.4     |           -----         |
 * 		      |							|						  |
 * UART4_TX   |      DMA1 St.4 Ch.4     |           -----         |
 * UART4_RX   |      DMA1 St.2 Ch.4     |           -----         |
 * 		      |						    |						  |
 * UART5_TX   | 	 DMA1 St.7 Ch.4     |           -----         |
 * UART5_RX   |      DMA1 St.0 Ch.4     | 	        -----         |
 * 		      |						    |						  |
 * USART6_TX  | 	 DMA2 St.6 Ch.5     |	   DMA2 St.7 Ch.5	  |
 * USART6_RX  | 	 DMA2 St.1 Ch.5     |	   DMA2 St.2 Ch.5	  |
 *			  |							|						  |
 * UART7_TX	  | 	 DMA1 St.1 Ch.5     |			-----		  |
 * UART7_RX	  | 	 DMA1 St.3 Ch.5     |			-----		  |
 *			  |							|						  |
 * UART8_TX   | 	 DMA1 St.0 Ch.5     |			-----		  |
 * UART8_RX   | 	 DMA1 St.6 Ch.5     |			-----		  |
 *
 */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_USART_H
#define __USH_STM32F4XX_USART_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Structures and enumerations
//---------------------------------------------------------------------------

/**
 * @brief USART pinsPack enumeration to select pins combination for U(S)ART
 */
typedef enum
{
	USART_PINSPACK_1	= 0x00U,	/* pinsPack1 selected */
	USART_PINSPACK_2				/* pinsPack2 selected */
} USH_USART_pinsPack;

/**
 * @brief USART dmaPack enumeration to select DMA combination for U(S)ART
 */
typedef enum
{
	USART_DMAPACK_1	= 0x00U,	/* DMAPack1 selected */
	USART_DMAPACK_2				/* DMAPack2 selected */
} USH_USART_dmaPack;

/**
 * @brief USART pinsPack enumeration to select a mode for U(S)ART
 */
typedef enum
{
	USART_MODE_RX	= 0x00U,	/* only RX selected */
	USART_MODE_TX,				/* only TX selected */
	USART_MODE_RX_TX			/* RX and TX selected */
} USH_USART_mode;

/**
  * @brief UART initialization structure definition
  */
typedef struct
{
	USART_TypeDef* USARTx;			/* A pointer to U(S)ART peripheral to be used where x is between 1 to 8 */

	USH_USART_pinsPack PinsPack;	/* U(S)ART pinsPack enumeration to select pins combination for U(S)ART.
								   	   This parameter can be a value of @ref USH_USART_pinsPack */

	USH_USART_dmaPack DmaPack;		/* DMA pack enumeration to select DMA for U(S)ART.
								   	   This parameter can be a value of @ref USH_USART_dmaPack */

	uint32_t BaudRate;				/* The special value which will be used to configure the UART communication baud rate.
								   	   The baud rate is computed using the following formula:
								   	   	   - IntegerDivider = ((PCLKx) / (8 * (OVR8 + 1) * (BaudRate)))
								   	   	   - FractionalDivider = ((IntegerDivider - ((uint32_t)IntegerDivider)) * 8 * (OVR8+1)) + 0.5
	                                     	 Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

	USH_USART_mode Mode;			/* U(S)ART modes selection. This parameter can be a value of @ref USH_USART_mode */

} USH_USART_initTypeDef;

//---------------------------------------------------------------------------
// External function prototypes
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
void USART_init(USH_USART_initTypeDef *initStructure);

#endif /* __USH_STM32F4XX_USART_H */
