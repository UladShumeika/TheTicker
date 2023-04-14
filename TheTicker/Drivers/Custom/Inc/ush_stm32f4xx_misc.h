/**
  ******************************************************************************
  * @file    ush_stm32f4xx_misc.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    27-February-2023
  * @brief   Header file of miscellaneous module.
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_MISC_H
#define __USH_STM32F4XX_MISC_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Structures and enumerations
//---------------------------------------------------------------------------

/**
 * @brief Flash latency enumeration
 */
typedef enum
{
	FLASH_LATENCY_0,		/* Flash zero latency cycle */
	FLASH_LATENCY_1,		/* Flash one latency cycle */
	FLASH_LATENCY_2,		/* Flash two latency cycle */
	FLASH_LATENCY_3,		/* Flash three latency cycle */
	FLASH_LATENCY_4,		/* Flash four latency cycle */
	FLASH_LATENCY_5,		/* Flash five latency cycle */
	FLASH_LATENCY_6,		/* Flash six latency cycle */
	FLASH_LATENCY_7,		/* Flash seven latency cycle */
	FLASH_LATENCY_8,		/* Flash eight latency cycle */
	FLASH_LATENCY_9,		/* Flash nine latency cycle */
	FLASH_LATENCY_10,		/* Flash ten latency cycle */
	FLASH_LATENCY_11,		/* Flash eleven latency cycle */
	FLASH_LATENCY_12,		/* Flash twelve latency cycle */
	FLASH_LATENCY_13,		/* Flash thirteen latency cycle */
	FLASH_LATENCY_14,		/* Flash fourteen latency cycle */
	FLASH_LATENCY_15,		/* Flash fifteen latency cycle */
} USH_FLASH_latency;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

/**
  * @brief  This function enables or disables the prefetch buffer.
  * @param  newState - A new state of the prefetch buffer.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_prefetchBufferCmd(FunctionalState newState);

/**
  * @brief  This function enables or disables the instruction cache feature.
  * @param  newState - A new state of the instruction cache.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_instructionCacheCmd(FunctionalState newState);

/**
  * @brief  This function enables or disables the data cache feature.
  * @param  newState - A new state of the data cache.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_dataCacheCmd(FunctionalState newState);

/**
  * @brief  This function sets the code latency value.
  * @param  flashLatency - specifies the FLASH Latency value.
  *          			   This parameter can be a value of @ref USH_FLASH_latency.
  *
  * @note For STM32F405xx/407xx, STM32F415xx/417xx, STM32F401xx/411xE/STM32F412xG and STM32F413_423xx devices
  *       this parameter can be a value between FLASH_LATENCY_0 and FLASH_LATENCY_7.
  *
  * @note For STM32F42xxx/43xxx devices this parameter can be a value between
  *       FLASH_LATENCY_0 and FLASH_LATENCY_15.
  *
  * @retval None
  */
void MISC_FLASH_setLatency(USH_FLASH_latency flashLatency);

#endif /* __USH_STM32F4XX_MISC_H */
