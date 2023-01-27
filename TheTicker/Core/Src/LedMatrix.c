//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "LedMatrix.h"
#include "string.h"
#include "fonts_max7219.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define USED_SPI					(SPI1)
#define SPEED_SHIFT					((uint8_t)60)

#define MATRIX_ROW					((uint8_t)4)
#define MATRIX_COLUMN				((uint8_t)8)

#define SHIFT_BYTE					((uint8_t)7)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId sendToTheMatrixHandle;
static osThreadId convertStringHandle;
osSemaphoreId mutexForMessageHandle;
static osMessageQId fromConvertToOutputHandle;
extern osMessageQId fromUartToMatrixHandle;

//---------------------------------------------------------------------------
// Static functions
//---------------------------------------------------------------------------
static void outputOnMatrix(uint8_t** outputBuffer, uint8_t max_column);
static void shiftOutputBuffer(uint8_t** outputBuffer, uint8_t rowBuffer, uint8_t columnBuffer);
static uint8_t** convertStringIntoDataForMatrix(UART_messageTypeDef *message, const uint8_t fontArray[][MATRIX_COLUMN]);

uint8_t **outputBuffer;

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
* @brief Function implementing the sending to the matrix thread.
* @param argument: Not used
* @retval None
*/
void SendToTheMatrixTask(void const * argument)
{
	uint8_t rowBuffer = 24;

	MAX7219_init();

	/* Infinite loop */
	for(;;)
	{

		outputOnMatrix(outputBuffer, MATRIX_COLUMN);
		shiftOutputBuffer(outputBuffer, rowBuffer, MATRIX_COLUMN);
		osDelay(SPEED_SHIFT);
		MAX7219_clean(ALL_DIGITS);
	}
}

/**
 * @brief 	Function implementing the converting the string to the matrix thread.
 * @param  	argument - Not used.
 * @retval	None.
 */
void convertStringIntoDataForMatrixTask(void const *argument)
{
	UART_messageTypeDef *message;
	osEvent evt;

	/* Infinite loop */
	for(;;)
	{
		evt = osMessageGet(fromUartToMatrixHandle, osWaitForever);

		if(evt.status == osEventMessage)
		{
			message = evt.value.p;
			outputBuffer = convertStringIntoDataForMatrix(message, font_ASCII);
		}
	}
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief  FreeRTOS initialization for LedMatrix module
  * @param  None
  * @retval None
  */
void LEDMATRIX_freeRtosInit(void)
{
	// Create the thread(s)
	// definition and creation of HeartbeatTask
	osThreadDef(SendToTheMatrix, SendToTheMatrixTask, osPriorityLow, 0, 128);
	sendToTheMatrixHandle = osThreadCreate(osThread(SendToTheMatrix), NULL);

	// definition and creation of convertStringIntoDataForMatrixTask
	osThreadDef(convertString, convertStringIntoDataForMatrixTask, osPriorityLow, 0, 128);
	convertStringHandle = osThreadCreate(osThread(convertString), NULL);

	// Create the queue(s)
	// definition and creating of fromConvertToOutputHandle
	osMessageQDef(fromConvertToOutput, 1, uint32_t);
	fromConvertToOutputHandle = osMessageCreate(osMessageQ(fromConvertToOutput), NULL);

	// Create the semaphore(s)
	// definition and creation of mutex for a message
	osSemaphoreDef(mutexForMessage);
	mutexForMessageHandle = osSemaphoreCreate(osSemaphore(mutexForMessage), 1);

#ifdef DEBUG
	vQueueAddToRegistry(mutexForMessageHandle, "mutex for a message");
#endif
}

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief	This function outputs information from the output buffer to the matrix.
 * @param 	outputBuffer - The special buffer that contains useful information for output to the matrix.
 * @retval	None.
 */
static void outputOnMatrix(uint8_t** outputBuffer, uint8_t max_column)
{
	//uint8_t matrix_row = strlen((char*)str);
	uint8_t matrix_row = 24;

	for(uint8_t column = 0; column < MATRIX_COLUMN; column++)
	{
		SPI_csPin(LOW);
		for(int8_t row = matrix_row - 1; row >= 0; row--)
		{
			SPI_writeData(USED_SPI, column + 1, outputBuffer[row][column]);
		}
		SPI_csPin(HIGH);
	}
}

/**
 * @brief 	This function shifts data into the output buffer.
 * @note	To understand how shift works. You need to understand that the matrix driver "flips" the data it receives.
 * 			For example, it is necessary that the LEDs 10011000 light up. For the matrix itself, the numbering will be
 * 			carried out as L10011000M. However, this number is stored in memory as M00011001L. In this regard,
 * 			when it is necessary to shift the displayed data to the left, then in fact in the code they need to be
 * 			shifted to the right. Also, when we check the extreme bit for a 1 in order to move it to the adjacent
 * 			matrix, then we need to keep track of the low bit in the code, and not the high bit.
 * 			And move it to the place of the older one in the adjacent matrix, and not the younger one.
 * @param 	outputBuffer - The special buffer that contains useful information for output to the matrix.
 * @retval	None.
 */
static void shiftOutputBuffer(uint8_t** outputBuffer, uint8_t rowBuffer, uint8_t columnBuffer)
{
	uint8_t tempBuffer[MATRIX_COLUMN] = {0,};

	for(uint8_t row = 0; row < rowBuffer; row++)
	{
		for(uint8_t column = 0; column < columnBuffer; column++)
		{
			if(row == 0)				// For the extreme matrix, we move the transitional 1 array from the buffer.
			{
				tempBuffer[column] = outputBuffer[row][column] & 0x01;
				outputBuffer[row][column] = outputBuffer[row][column] >> 1;
			} else
			{
				outputBuffer[row - 1][column] |= (outputBuffer[row][column] & 0x01) << SHIFT_BYTE;
				outputBuffer[row][column] = outputBuffer[row][column] >> 1;
			}

			if(row == rowBuffer - 1)	// For the last matrix, add transition units from the buffer.
			{
				outputBuffer[row][column] = outputBuffer[row][column] | (tempBuffer[column] << SHIFT_BYTE);
			}
		}
	}
}

static uint8_t** convertStringIntoDataForMatrix(UART_messageTypeDef *message, const uint8_t fontArray[][MATRIX_COLUMN])
{
	//uint8_t sizeStr = strlen((char*)str);
	uint8_t sizeStr = message->sizeMessage;
	uint8_t m = MATRIX_COLUMN;
	uint8_t symbol = 0;

	uint8_t **buffer = (uint8_t**)pvPortMalloc(sizeStr * sizeof(uint8_t*) + sizeStr * m * sizeof(uint8_t));
	uint8_t *start = ((uint8_t*)buffer + sizeStr * sizeof(uint8_t*));

	for(uint8_t i = 0; i < sizeStr; i++)
		buffer[i] = start + i * m;

	for(uint8_t row = 0; row < sizeStr; row++)
	{
		for(uint8_t column = 0; column < MATRIX_COLUMN; column++)
		{
			symbol = (uint8_t)(message->message[row] - 0x21 + 0x01);
			buffer[row][column] = font_ASCII[symbol][column];
		}
	}

	return buffer;
}
