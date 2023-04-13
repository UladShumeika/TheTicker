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
}
