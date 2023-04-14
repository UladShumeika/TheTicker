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

#define RX_BUFFER_SIZE	(256U)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId idleIRQTaskHandle;
static osPoolId	messageStructHandle;
osMessageQId fromUartToMatrixHandle;
static osSemaphoreId idleIRQHandle;

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void UART_init(void);

//---------------------------------------------------------------------------
// Description of peripheral structures
//--------------------------------------------------------------------------
USH_USART_initTypeDef uart_structure = {0};

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
static uint8_t rxBuffer[RX_BUFFER_SIZE];
static const uint8_t defaultString[] = "Hi, please enter your message. ";
static const uint8_t welcomeString[] = "Hi, please enter your message.\r\n";
static const uint8_t noteMessage[] = "NOTE: Every message has to have only one system symbol (\\n).\r\n";

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

	UART_init();

	USART_receiveToIdleDMA(USED_UART, rxBuffer, sizeof(rxBuffer));
	USART_transmitDMA(USED_UART, (uint8_t*)welcomeString, strlen((char*)welcomeString));
	USART_transmitDMA(USED_UART, (uint8_t*)noteMessage, strlen((char*)noteMessage));

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

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function returns a pointer to the default string.
 * @retval	A pointer to the default string.
 */
uint8_t* getPointerDefaultString(void)
{
	return (uint8_t*)defaultString;
}

//---------------------------------------------------------------------------
// Callbacks
//---------------------------------------------------------------------------

/**
 * @brief  IDLE callbacks.
 * @param  usart - A pointer to U(S)ART peripheral to be used where x is between 1 to 8.
 * @retval None.
 */
void USART_idleCallback(USART_TypeDef* usart)
{
	if(usart == USED_UART) osSemaphoreRelease(idleIRQHandle);
}
