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
// Defines
//---------------------------------------------------------------------------
#define SYS_TICK_PRIORITY			(15U)
#define SYS_TICK_1MS				(1000U)

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void initMicrocontroller(void);
static ErrorStatus initSysTick(uint32_t tickPriority);
static ErrorStatus initSystemClock(void);

//---------------------------------------------------------------------------
// Main function
//---------------------------------------------------------------------------

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint8_t status;

	initMicrocontroller();

	status = initSystemClock();
	if(!status);

	status = initSysTick(SYS_TICK_PRIORITY);
	if(!status);

	// Call init function for freertos objects (in freertos.c)
	MX_FREERTOS_Init();

	// Start scheduler
	osKernelStart();

    // Loop forever
	for(;;);
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief This function is used to initialize system clock
  * @retval ErrorStatus Status
  */
static ErrorStatus initSystemClock(void)
{
	// Configure the main internal regulator output voltage
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN, ENABLE);
	PWR_MainRegulatorModeConfig(PWR_Regulator_Voltage_Scale1);

	// Configure the External High Speed oscillator (HSE)
	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp());

}

/**
  * @brief	This function is used to initialize SysTick. The SysTick is configured
  * 		to have 1ms time base with a dedicated Tick interrupt priority
  * @param 	tickPriority Tick interrupt priority
  * @retval	ErrorStatus Status
  */
static ErrorStatus initSysTick(uint32_t tickPriority)
{
	// Configure the SysTick to have interrupt in 1ms time basis
	if(SysTick_Config(SystemCoreClock / SYS_TICK_1MS) > 0U)
	{
		return ERROR;
	}

	// Configure the SysTick IRQ priority
	if(tickPriority < (1UL << __NVIC_PRIO_BITS))
	{
		NVIC_SetPriority(SysTick_IRQn, tickPriority);
	} else
		{
			return ERROR;
		}

	return SUCCESS;
}

/**
  * @brief 	This function is used to initialize the main nodes of the microcontroller to run.
  * 		It performs the following:
  * 			Configure Flash prefetch, Instruction cache, Data cache;
  * 			Set NVIC Group Priority to 4;
  * @retval None
  */
static void initMicrocontroller(void)
{
	// Configure Flash prefetch, Instruction cache, Data cache
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);

	// Set NVIC Group Priority to 4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
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
