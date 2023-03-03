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
// External function prototypes
//---------------------------------------------------------------------------

/**
  * @brief  This function sets the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32f4xxxx.h))
  * @param  PreemptPriority - The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15.
  *         A lower priority value indicates a higher priority.
  * @param  SubPriority - The subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15.
  *         A lower priority value indicates a higher priority.
  * @retval	None.
  */
void MISC_NVIC_SetPriority(IRQn_Type IRQn, uint32_t preemptPriority, uint32_t subPriority);

#endif /* __USH_STM32F4XX_MISC_H */
