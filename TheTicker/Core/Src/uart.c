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
static uint8_t* messageCapture(USART_TypeDef* usart, uint8_t* sourceBuffer, uint16_t sizeSourceBuffer);

//---------------------------------------------------------------------------
// Description of peripheral structures
//--------------------------------------------------------------------------
USH_USART_initTypeDef uart_structure = {0,};

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
static uint8_t rxBuffer[RX_BUFFER_SIZE];
static uint8_t defaultString[] = "Hello! ";

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
	uint8_t* receivedString;
	uint8_t firstStart = 1;

	UART_init();
	USART_receiveToIdleDMA(USED_UART, rxBuffer, sizeof(rxBuffer));

	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(idleIRQHandle, osWaitForever);

		if(firstStart)
		{
			receivedString = defaultString;
			firstStart = 0;
		} else
		{
			receivedString = messageCapture(USED_UART, rxBuffer, sizeof(rxBuffer));
		}

		message->message = receivedString;
		message->sizeMessage = strlen((char*)receivedString);

		osMessagePut(fromUartToMatrixHandle, (uint32_t)message, osWaitForever);
	}
}

//---------------------------------------------------------------------------
// Static functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function parses the RX buffer and grabs messages from it.
 * @note	Each message has system characters at the end \r and \n. They are not needed for output to the matrix.
 * 			In the code, these two characters are replaced by one space (' ') character.
 * @param 	usart - A pointer to U(S)ART peripheral to be used where x is between 1 to 8.
 * @param 	sourceBuffer - A pointer to RX buffer.
 * @param 	sizeSourceBuffer - Size of RX buffer.
 * @retval	A pointer to the created string.
 */
static uint8_t* messageCapture(USART_TypeDef* usart, uint8_t* sourceBuffer, uint16_t sizeSourceBuffer)
{
	static uint16_t oldPosition	= 0;	// necessary variables to calculate the length of the received message
	uint16_t position			= 0;	// and the index in the RX buffer
	uint8_t sizeString 			= 0;
	uint8_t* string;

	// Get DMA stream
	DMA_Stream_TypeDef* DMA_Stream = USART_getDmaStream(usart, USART_MODE_RX);

	position = sizeSourceBuffer - DMA_getNumberOfData(DMA_Stream);

	if(position > oldPosition)
	{
		sizeString = position - oldPosition;

		if(sizeString < OUTPUT_BUFFER_MIN_ROW)
		{
			string = (uint8_t*)pvPortMalloc(((OUTPUT_BUFFER_MIN_ROW + 1) * (sizeof(uint8_t))));
			memcpy(string, &sourceBuffer[oldPosition], 1);

			for(uint8_t i = 1; i < OUTPUT_BUFFER_MIN_ROW; i++)
			{
				string[i] = ' ';
			}

			string[OUTPUT_BUFFER_MIN_ROW + 1] = '\0';

		} else
		{
			string = (uint8_t*)pvPortMalloc(((sizeString + 1) * sizeof(uint8_t)));
			memset(string, ' ', sizeString);
			memcpy(string, &sourceBuffer[oldPosition], sizeString - 1);

			string[sizeString + 1] = '\0';
		}
	} else
	{
		if(position > 2)
		{
			sizeString = (sizeSourceBuffer - oldPosition) + (position);
		} else
		{
			sizeString = (sizeSourceBuffer - oldPosition);
		}
		string = (uint8_t*)pvPortMalloc(((sizeString + 1) * sizeof(uint8_t)));
		memcpy(string, &sourceBuffer[oldPosition], sizeSourceBuffer - oldPosition);
		memcpy(&string[sizeSourceBuffer - oldPosition], sourceBuffer, sizeString - (sizeSourceBuffer - oldPosition) - 1);
	}

	//string[sizeString - 2] = ' ';
	//string[sizeString - 1] = '\0';

	oldPosition = position;

	if(oldPosition == (RX_BUFFER_SIZE - 1)) oldPosition = 0;

	return string;
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
	osThreadDef(idleIRQ, idleIRQTask, osPriorityLow, 0, 192);
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
