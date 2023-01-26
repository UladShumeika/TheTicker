//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "LedMatrix.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId sendToTheMatrixHandle;

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
uint8_t outputBuffer[4][8] = {{0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18}, 	// O
		                      {0x81, 0x81, 0xFF, 0x81, 0x81, 0x42, 0x24, 0x18},		// A
							  {0x08, 0x04, 0x02, 0xFF, 0xFF, 0x02, 0x04, 0x08},		// <-
							  {0x0C, 0x34, 0x44, 0x44, 0x44, 0x44, 0x34, 0x0C}};	// D

//---------------------------------------------------------------------------
// Static functions
//---------------------------------------------------------------------------
void outputOnMatrix(uint8_t outputBuffer[][8]);
void shift_outputBuffer(uint8_t outputBuffer[][8]);

void addNewDataToOutputBuffer(uint8_t outputBuffer[][4], uint8_t dataBuffer[8]);

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
//	shift_outputBuffer(outputBuffer);
	//addNewDataToOutputBuffer(outputBuffer, dataBuffer);

	//outputOnMatrix(&outputBuffer);

	/* Infinite loop */
	for(;;)
	{
		outputOnMatrix(outputBuffer);
		shift_outputBuffer(outputBuffer);
		osDelay(1000);
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
