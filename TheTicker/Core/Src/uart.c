//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "uart.h"
#include "string.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId idleIRQTaskHandle;
static osPoolId	messageStructHandle;
osMessageQId fromUartToMatrixHandle;
static osSemaphoreId idleIRQHandle;

static const uint8_t defaultString[] = "Hi, please enter your message. ";

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
 * @brief 	Function implementing the processing of received data by USART1
 * @param 	argument - Not used.
 * @retval  None.
 */
void idleIRQTask(void const *argument)
{
	UART_messageTypeDef *message = (UART_messageTypeDef*)osPoolCAlloc(messageStructHandle);
	uint8_t flagFirstStart = 1;

	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(idleIRQHandle, osWaitForever);

		if(flagFirstStart)
		{
			message->message = (uint8_t*)defaultString;
			message->sizeMessage = strlen((char*)defaultString);

			flagFirstStart = 0;
		} else
		{
		}

		osMessagePut(fromUartToMatrixHandle, (uint32_t)message, osWaitForever);
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
	// definition and creation of idleIRQTask
	osThreadDef(idleIRQ, idleIRQTask, osPriorityLow, 0, 256);
	idleIRQTaskHandle = osThreadCreate(osThread(idleIRQ), NULL);

	// Create the queue(s)
	// definition and creating of fromUartToMatrixHandle
	osMessageQDef(fromUartToMatrix, 1, UART_messageTypeDef);
	fromUartToMatrixHandle = osMessageCreate(osMessageQ(fromUartToMatrix), NULL);

	// Create the memory pool(s)
	// definition and creating of messageStructHandle
	osPoolDef(messagePool, 1, UART_messageTypeDef);
	messageStructHandle = osPoolCreate(osPool(messagePool));

	// Create the semaphore(s)
	// definition and creating of idleIRQHandle
	osSemaphoreDef(idleIRQ);
	idleIRQHandle = osSemaphoreCreate(osSemaphore(idleIRQ), 1);

#ifdef DEBUG
	vQueueAddToRegistry(fromUartToMatrixHandle, "from uart");
	vQueueAddToRegistry(idleIRQHandle, "IDLE IRQ");
#endif
}
