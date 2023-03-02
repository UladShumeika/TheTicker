/**
  ******************************************************************************
  * @file    ush_stm32f4xx_misc.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    27-February-2023
  * @brief   This file contains the functions's prototypes for the miscellaneous
  *          firmware library functions.
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
 * @brief Periphery status enumeration.
 */
typedef enum
{
	STATUS_BUSY	 	= 0,				/* Periphery status busy */
	STATUS_OK	 	= !STATUS_BUSY		/* Periphery status ok */
} USH_peripheryStatus;

#endif /* __USH_STM32F4XX_MISC_H */
