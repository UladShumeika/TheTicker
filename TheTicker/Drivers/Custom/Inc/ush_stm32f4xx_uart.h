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

#endif /* __USH_STM32F4XX_USART_H */
