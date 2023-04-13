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
	/* Infinite loop */
	for(;;)
	{
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
}
