/**
  ******************************************************************************
  * @file    ush_stm32f4xx_usart.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    21-February-2023
  * @brief   Header file of U(S)ART module.
  *
  * NOTE: This file is not a full-fledged U(S)ART driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
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
 * @brief USART pinsPack enumeration to select a mode for U(S)ART
 */
typedef enum
{
	USART_MODE_RX		= 0x04U,	/* only RX selected */
	USART_MODE_TX		= 0x08U,	/* only TX selected */
	USART_MODE_RX_TX 	= 0x0CU		/* RX and TX selected */
} USH_USART_mode;

/**
  * @brief UART initialization structure definition
  */
typedef struct
{
	USART_TypeDef* USARTx;			/* A pointer to U(S)ART peripheral to be used where x is between 1 to 8 */

	USH_USART_pinsPack PinsPack;	/* U(S)ART pinsPack enumeration to select pins combination for U(S)ART.
								   	   This parameter can be a value of @ref USH_USART_pinsPack */

	uint32_t BaudRate;				/* The special value which will be used to configure the UART communication baud rate.
								   	   The baud rate is computed using the following formula:
								   	   	   - IntegerDivider = ((PCLKx) / (8 * (OVR8 + 1) * (BaudRate)))
								   	   	   - FractionalDivider = ((IntegerDivider - ((uint32_t)IntegerDivider)) * 8 * (OVR8+1)) + 0.5
	                                     	 Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

	USH_USART_mode Mode;			/* U(S)ART modes selection. This parameter can be a value of @ref USH_USART_mode */

} USH_USART_initTypeDef;

#endif /* __USH_STM32F4XX_USART_H */
