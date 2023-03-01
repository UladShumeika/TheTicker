//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "uart.h"
#include "string.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

// Configuration UART
#define USED_UART		(USART1)
#define USED_PINSPACK	(USART_PINSPACK_1)
#define USED_BAUDRATE	((uint32_t)115200)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId receivingMessageHandle;
osMessageQId fromUartToMatrixHandle;
static osPoolId	messageStructHandle;
extern osSemaphoreId mutexForMessageHandle;

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void UART_init(void);

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
static uint8_t string[] = "Hello, my name is Ulad! ";

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
	UART_messageTypeDef *message;
	message = (UART_messageTypeDef*) osPoolCAlloc(messageStructHandle);

	message->message = string;
	message->sizeMessage = strlen((char*)string);

	osMessagePut(fromUartToMatrixHandle, (uint32_t)message, osWaitForever);

	UART_init();

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
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

	// Create the memory pool(s)
	// definition and creating of messageStructHandle
	osPoolDef(messagePool, 1, UART_messageTypeDef);
	messageStructHandle = osPoolCreate(osPool(messagePool));

#ifdef DEBUG
	vQueueAddToRegistry(fromUartToMatrixHandle, "from uart");
#endif
}

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes U(S)ART module.
 * @retval	None.
 */
static void UART_init(void)
{
	USH_USART_initTypeDef uart_structure = {0,};

	uart_structure.USARTx 		= USED_UART;
	uart_structure.PinsPack 	= USED_PINSPACK;
	uart_structure.BaudRate 	= USED_BAUDRATE;
	uart_structure.Mode 		= USART_MODE_RX_TX;
	USART_init(&uart_structure);
}
