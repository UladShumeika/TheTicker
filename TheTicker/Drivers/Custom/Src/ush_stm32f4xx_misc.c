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
// The section of FLASH memory
//---------------------------------------------------------------------------

/**
  * @brief  This function enables or disables the prefetch buffer.
  * @param  newState - A new state of the prefetch buffer.
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

/**
  * @brief  This function enables or disables the instruction cache feature.
  * @param  newState - A new state of the instruction cache.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_instructionCacheCmd(FunctionalState newState)
{
  // Check the parameters
  assert_param(IS_FUNCTIONAL_STATE(newState));

  if(newState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_ICEN;
  }
  else
  {
    FLASH->ACR &= (~FLASH_ACR_ICEN);
  }
}

/**
  * @brief  This function enables or disables the data cache feature.
  * @param  newState - A new state of the data cache.
  *          		   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void MISC_FLASH_dataCacheCmd(FunctionalState newState)
{
  // Check the parameters
  assert_param(IS_FUNCTIONAL_STATE(newState));

  if(newState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_DCEN;
  }
  else
  {
    FLASH->ACR &= (~FLASH_ACR_DCEN);
  }
}

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
void MISC_FLASH_setLatency(USH_FLASH_latency flashLatency)
{
  // Check the parameters
  assert_param(IS_MISC_FLASH_LATENCY(flashLatency));

  // Perform Byte access to FLASH_ACR[8:0] to set the Latency value
  *(__IO uint8_t *)FLASH_ACR_BYTE0_ADDRESS = (uint8_t)flashLatency;
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
