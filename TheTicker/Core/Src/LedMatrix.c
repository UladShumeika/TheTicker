//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "LedMatrix.h"
#include "string.h"
#include "fonts_max7219.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

// Configuration SPI
#define USED_SPI			(MATRIX_SPI)
#define USED_PINSPACK		((SPI_PINSPACK_1))
#define USED_PRESCALER		((SPI_BAUDRATE_PRESCALER_16))

#define SPEED_SHIFT			((uint8_t)60)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId sendToTheMatrixHandle;
static osThreadId convertStringHandle;
extern osMessageQId fromUartToMatrixHandle;

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void outputOnMatrix(uint8_t** outputBuffer);
static uint8_t** convertStringIntoDataForMatrix(UART_messageTypeDef *message, const uint8_t fontArray[][ASCII_COLUMN]);

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
static uint8_t **outputBuffer;
static uint8_t rowBuffer;

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
 * @brief 	Function implementing the sending to the matrix thread.
 * @param 	argument - Not used.
 * @retval  None.
 */
void sendToTheMatrixTask(void const *argument)
{
	MAX7219_init(USED_SPI, USED_PINSPACK, USED_PRESCALER);

	/* Infinite loop */
	for(;;)
	{
		outputOnMatrix(outputBuffer);
		osDelay(SPEED_SHIFT);
	}
}

/**
 * @brief 	Function implementing the converting the string to the matrix thread.
 * @param  	argument - Not used.
 * @retval	None.
 */
void convertStringIntoDataForMatrixTask(void const *argument)
{
	osEvent evt;
	UART_messageTypeDef *message;
	uint8_t firstStart = 1;

	/* Infinite loop */
	for(;;)
	{
		evt = osMessageGet(fromUartToMatrixHandle, osWaitForever);

		if(evt.status == osEventMessage)
		{

			message = evt.value.p;
			rowBuffer = message->sizeMessage;

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
	// definition and creation of sendToTheMatrixTask
	osThreadDef(SendToTheMatrix, sendToTheMatrixTask, osPriorityLow, 0, 128);
	sendToTheMatrixHandle = osThreadCreate(osThread(SendToTheMatrix), NULL);

	// definition and creation of convertStringIntoDataForMatrixTask
	osThreadDef(convertString, convertStringIntoDataForMatrixTask, osPriorityLow, 0, 128);
	convertStringHandle = osThreadCreate(osThread(convertString), NULL);


}

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief	This function outputs information from the output buffer to the LED matrix.
 * @note	A pointer to a dynamic 2D buffer is passed to this function without specifying its size,
 * 			since the "output window" of information corresponds to the number of digits of the LED matrix.
 * 			For example, if a LED matrix module with 4 digits is available, then a dynamic array must be created
 * 			for at least 4 characters. !!!If you create a dynamic array smaller than the LED matrix "output window",
 * 			then this will lead to an overflow of the array!!!.
 * @param 	outputBuffer - A pointer to output buffer that contains the useful information for
 * 						   outputting to the LED matrix.
 * @retval	None.
 */
static void outputOnMatrix(uint8_t** outputBuffer)
{
	for(uint8_t column = 0; column < OUTPUT_BUFFER_COLUMN; column++)
	{
		SPI_csPin(MATRIX_CS_PORT, MATRIX_CS_PIN, LOW);
		for(int8_t row = OUTPUT_BUFFER_MIN_ROW - 1; row >= 0; row--)
		{
			SPI_writeData(MATRIX_SPI, column + 1, outputBuffer[row][column]);
		}
		SPI_csPin(MATRIX_CS_PORT, MATRIX_CS_PIN, HIGH);
	}
}

/**
 * @brief 	This function converts the received message into the special data for the LED matrix.
 * @param 	message - A pointer to the message structure.
 * @param 	fontArray - The special array that has ASCII font information.
 * @retval	A pointer to a dynamic 2D buffer.
 */
static uint8_t** convertStringIntoDataForMatrix(UART_messageTypeDef *message, const uint8_t fontArray[][ASCII_COLUMN])
{
	uint8_t sizeMessage = message->sizeMessage;
	uint8_t symbol = 0;

/* -------------------------------- Dynamic allocation memory ---------------------------------------*/

	uint8_t **outputBuffer = (uint8_t**)pvPortMalloc(sizeMessage * sizeof(uint8_t*) + sizeof(uint8_t) * OUTPUT_BUFFER_COLUMN * sizeMessage);
	uint8_t *startData = ((uint8_t*)outputBuffer + sizeMessage * sizeof(uint8_t*));

	for(uint8_t counter = 0; counter < sizeMessage; counter++)
		outputBuffer[counter] = startData + counter * OUTPUT_BUFFER_COLUMN;

/* ------ Filling the created array with information about symbols for output to the LED matrix -----*/

	for(uint8_t row = 0; row < sizeMessage; row++)
	{
		for(uint8_t column = 0; column < OUTPUT_BUFFER_COLUMN; column++)
		{
			symbol = (uint8_t)(message->message[row] - ASCII_SHIFT);
			if(symbol >= ASCII_ROW) symbol = 0;	// see font_ASCII buffer for more information

			outputBuffer[row][column] = font_ASCII[symbol][column];
		}
	}

	return outputBuffer;
}
