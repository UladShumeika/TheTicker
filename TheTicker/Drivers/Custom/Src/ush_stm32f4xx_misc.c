/**
  ******************************************************************************
  * @file    ush_stm32f4xx_misc.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    27-February-2023
  * @brief	 This file contains the implementation of functions for the miscellaneous
  * 		 firmware library functions.
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_misc.h"
#include <stdio.h>

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------
#define IS_NVIC_SUB_PRIORITY(PRIORITY)  		((PRIORITY) < 16U)
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  	((PRIORITY) < 16U)

//---------------------------------------------------------------------------
// Redefine printf function
//---------------------------------------------------------------------------
int _write(int file, char *ptr, int len)
{
	for(int i=0 ; i < len ; i++)
	{
		ITM_SendChar((*ptr++));
	}

  return len;
}

//---------------------------------------------------------------------------
// The section of NVIC
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
void MISC_NVIC_SetPriority(IRQn_Type IRQn, uint32_t preemptPriority, uint32_t subPriority)
{
  uint32_t prioritygroup = 0x00U;

  // Check the parameters
  assert_param(IS_NVIC_SUB_PRIORITY(subPriority));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(preemptPriority));

  prioritygroup = NVIC_GetPriorityGrouping();

  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, preemptPriority, subPriority));
}

//---------------------------------------------------------------------------
// The section of FLASH memory
//---------------------------------------------------------------------------

/**
  * @brief  This function enables or disables the prefetch buffer.
  * @param  newState - a new state of the prefetch buffer.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_prefetchBufferCmd(FunctionalState newState)
{
  // Check the parameters
  assert_param(IS_FUNCTIONAL_STATE(newState));

  // Enable or disable the prefetch buffer
  if(newState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_PRFTEN;
  }
  else
  {
    FLASH->ACR &= (~FLASH_ACR_PRFTEN);
  }
}

//---------------------------------------------------------------------------
// Function's parameters check.
//---------------------------------------------------------------------------
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
	printf("Wrong parameters value: file %s on line %ld\r\n", file, line);
}
#endif /* USE_FULL_ASSERT */
