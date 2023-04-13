//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "LedMatrix.h"
#include "string.h"
#include "fonts_max7219.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId sendToTheMatrixHandle;
static osThreadId convertStringHandle;

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
	/* Infinite loop */
	for(;;)
	{
	}
}

/**
 * @brief 	Function implementing the converting the string to the matrix thread.
 * @param  	argument - Not used.
 * @retval	None.
 */
void convertStringIntoDataForMatrixTask(void const *argument)
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
