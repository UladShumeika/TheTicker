//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "heartbeat.h"

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId HeartbeatHandle;

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
* @brief Function implementing the heartbeat thread.
* @param argument: Not used
* @retval None
*/
void HeartbeatTask(void const * argument)
{
  //HEARTBEAT_GPIO_Init();

  /* Infinite loop */
  for(;;)
  {
	//HAL_GPIO_TogglePin(PORT_LED_HEARTBEAT, PIN_LED_HEARTBEAT);
    //osDelay(BLICK_DELAY_HEARTBEAT);
	  osDelay(1);
  }
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief  FreeRTOS initialization for heartbeat module
  * @param  None
  * @retval None
  */
void HEARTBEAT_freeRtosInit(void)
{
	// Create the thread(s)
	// definition and creation of HeartbeatTask
	osThreadDef(Heartbeat, HeartbeatTask, osPriorityLow, 0, 128);
	HeartbeatHandle = osThreadCreate(osThread(Heartbeat), NULL);
}
