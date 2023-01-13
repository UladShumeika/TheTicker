/*
 * The pet project -
 *
 *  Created on: Jan 13, 2023
 *      Author: Ulad Shumeika
 */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void initMicrocontroller(void);

static void SystemClock_Config(void);

//---------------------------------------------------------------------------
// Main function
//---------------------------------------------------------------------------

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	initMicrocontroller();

	SystemClock_Config();

	// Call init function for freertos objects (in freertos.c)
	MX_FREERTOS_Init();

	// Start scheduler
	osKernelStart();

    /* Loop forever */
	for(;;);
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief 	This function is used to initialize the main nodes of the microcontroller to run.
  * It performs the following:
  * 	Configure Flash prefetch, Instruction cache, Data cache;
  * 	Set NVIC Group Priority to 4;
  * 	Configure the SysTick to generate an interrupt each 1 millisecond
  * @retval None
  */
static void initMicrocontroller(void)
{
	// Configure Flash prefetch, Instruction cache, Data cache
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

}

#ifdef  USE_FULL_ASSERT
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
