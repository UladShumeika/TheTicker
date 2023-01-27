//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "uart.h"
#include "string.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId receivingMessageHandle;
static osMessageQId fromUartToMatrixHandle;
extern osSemaphoreId mutexForMessageHandle;

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

	// Create the queue(s)
	// definition and creating of fromUartToMatrixHandle
	osMessageQDef(fromUartToMatrix, 1, UART_messageTypeDef);
	fromUartToMatrixHandle = osMessageCreate(osMessageQ(fromUartToMatrix), NULL);

#ifdef DEBUG
	vQueueAddToRegistry(fromUartToMatrixHandle, "from uart");
#endif
}
