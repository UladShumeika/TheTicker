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

}
