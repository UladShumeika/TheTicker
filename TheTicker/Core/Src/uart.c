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

#define RX_BUFFER_SIZE	(20U)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId receivingMessageHandle;
static osThreadId idleIRQTaskHandle;
static osPoolId	messageStructHandle;
osMessageQId fromUartToMatrixHandle;
osSemaphoreId idleIRQHandle;

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void UART_init(void);

//---------------------------------------------------------------------------
// Description of peripheral structures
//--------------------------------------------------------------------------
USH_USART_initTypeDef uart_structure = {0,};

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
static uint8_t Rx_buffer[RX_BUFFER_SIZE];

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
		USART_transmitDMA(USART1, string, sizeof(string));
		osDelay(1000);
	}
}

/**
 * @brief 	Function implementing the processing of received data by USART1
 * @param 	argument - Not used.
 * @retval  None.
 */
void idleIRQTask(void const *argument)
{
	uint8_t firstStart = 1;

	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(idleIRQHandle, osWaitForever);

		// After a semaphore is created, it's in the released state. So, the message will only be processed when the interrupt occurs.
		if(!firstStart)
		{

		}
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

	// definition and creation of idleIRQTask
	osThreadDef(idleIRQ, idleIRQTask, osPriorityLow, 0, 128);
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

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes U(S)ART module.
 * @retval	None.
 */
static void UART_init(void)
{
	uart_structure.USARTx 		= USED_UART;
	uart_structure.PinsPack 	= USED_PINSPACK;
	uart_structure.BaudRate 	= USED_BAUDRATE;
	uart_structure.Mode 		= USART_MODE_RX_TX;
	USART_init(&uart_structure);
}
