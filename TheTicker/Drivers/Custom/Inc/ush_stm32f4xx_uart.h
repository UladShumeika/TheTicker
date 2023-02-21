/**
  ******************************************************************************
  * @file    ush_stm32f4xx_uart.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    21-February-2023
  * @brief   This file contains the functions prototypes for the UART firmware
  *          library.
  *
  * NOTE: This file is not a full-fledged UART driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_UART_H
#define __USH_STM32F4XX_UART_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Structures and enumerations
//---------------------------------------------------------------------------

/**
  * @brief UART initialization structure definition
  */
typedef struct
{
	USART_TypeDef* USARTx;		/* A pointer to U(S)ART peripheral to be used where x is between 1 to 8 */

	uint8_t PinsPack;			/* U(S)ART pinsPack enumeration to select pins combination for U(S)ART.
								   This parameter can be a value of @ref USH_USART_pinsPack */

	uint8_t DmaPack;			/* DMA pack enumeration to select DMA for U(S)ART.
								   This parameter can be a value of @ref USH_USART_dmaPack */

	uint32_t BaudRate;			/* The special value which will be used to configure the UART communication baud rate.
								   The baud rate is computed using the following formula:
								   	   - IntegerDivider = ((PCLKx) / (8 * (OVR8 + 1) * (BaudRate)))
								   	   - FractionalDivider = ((IntegerDivider - ((uint32_t)IntegerDivider)) * 8 * (OVR8+1)) + 0.5
	                                     Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

	uint16_t Mode;				/* U(S)ART modes selection. This parameter can be a value of @ref USH_USART_mode */

} USH_USART_initTypeDef;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

#endif /* __USH_STM32F4XX_UART_H */
