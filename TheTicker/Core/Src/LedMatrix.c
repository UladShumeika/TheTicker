//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "LedMatrix.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define USED_SPI					(SPI1)
#define SPEED_SHIFT					((uint8_t)100)

#define MATRIX_ROW					((uint8_t)4)
#define MATRIX_COLUMN				((uint8_t)8)

#define SHIFT_BYTE					((uint8_t)7)

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId sendToTheMatrixHandle;

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
uint8_t outputBuffer[MATRIX_ROW][MATRIX_COLUMN] = {{0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18}, 	// O
		                      	  	  	  	  	   {0x81, 0x81, 0xFF, 0x81, 0x81, 0x42, 0x24, 0x18},	// A
												   {0x08, 0x04, 0x02, 0xFF, 0xFF, 0x02, 0x04, 0x08},	// <-
												   {0x0C, 0x34, 0x44, 0x44, 0x44, 0x44, 0x34, 0x0C}};	// D

//---------------------------------------------------------------------------
// Static functions
//---------------------------------------------------------------------------
static void outputOnMatrix(uint8_t outputBuffer[][MATRIX_COLUMN]);
static void shift_outputBuffer(uint8_t outputBuffer[][MATRIX_COLUMN]);

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
	MAX7219_init();

	/* Infinite loop */
	for(;;)
	{
		outputOnMatrix(outputBuffer);
		shift_outputBuffer(outputBuffer);
		osDelay(SPEED_SHIFT);
		MAX7219_clean(ALL_DIGITS);
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
}

//---------------------------------------------------------------------------
// Others functions
//---------------------------------------------------------------------------

/**
 * @brief	This function outputs information from the output buffer to the matrix.
 * @param 	outputBuffer - The special buffer that contains useful information for output to the matrix.
 * @retval	None.
 */
static void outputOnMatrix(uint8_t outputBuffer[][MATRIX_COLUMN])
{
	for(uint8_t column = 0; column < MATRIX_COLUMN; column++)
	{
		SPI_csPin(LOW);
		for(int8_t row = MATRIX_ROW - 1; row >= 0; row--)
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
static void shift_outputBuffer(uint8_t outputBuffer[][MATRIX_COLUMN])
{
	uint8_t tempBuffer[MATRIX_COLUMN] = {0,};

	for(uint8_t row = 0; row < MATRIX_ROW; row++)
	{
		for(uint8_t column = 0; column < MATRIX_COLUMN; column++)
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

			if(row == MATRIX_ROW - 1)	// For the last matrix, add transition units from the buffer.
			{
				outputBuffer[row][column] = outputBuffer[row][column] | (tempBuffer[column] << SHIFT_BYTE);
			}
		}
	}
}

