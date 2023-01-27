//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "uart.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId receivingMessageHandle;

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
 * @brief 	Function implementing receiving a message thread.
 * @param 	argument - Not used.
 * @retval  None.
 */
void receivingMessageTask(void const *argument)
{
	/* Infinite loop */
	for(;;)
	{
		osDelay(1000);
	}
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief  FreeRTOS initialization for uart module
  * @param  None
  * @retval None
  */
void UART_freeRtosInit(void)
{
	// Create the thread(s)
	// definition and creation of receivingMessageTask
	osThreadDef(receivingMessage, receivingMessageTask, osPriorityLow, 0, 128);
	receivingMessageHandle = osThreadCreate(osThread(receivingMessage), NULL);
}
