//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "heartbeat.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define PORT_LED_HEARTBEAT				GPIOG
#define PIN_LED_HEARTBEAT				GPIO_PIN_13
#define BLICK_DELAY_HEARTBEAT			(1000U)				// ms

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void HEARTBEAT_gpioInit(void);

//---------------------------------------------------------------------------
// Descriptions of FreeRTOS elements
//---------------------------------------------------------------------------
static osThreadId heartbeatHandle;

//---------------------------------------------------------------------------
// FreeRTOS's threads
//---------------------------------------------------------------------------

/**
* @brief Function implementing the heartbeat thread.
* @param argument: Not used
* @retval None
*/
void heartbeatTask(void const * argument)
{
	HEARTBEAT_gpioInit();

	/* Infinite loop */
	for(;;)
	{
		GPIO_toggleBits(PORT_LED_HEARTBEAT, PIN_LED_HEARTBEAT);
		osDelay(BLICK_DELAY_HEARTBEAT);
	}
}

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
  * @brief  GPIO configuration for heartbeat module
  * @param  None
  * @retval None
  */
static void HEARTBEAT_gpioInit(void)
{
	USH_GPIO_initTypeDef GPIO_InitStruct = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOGEN, ENABLE);

	// Configure GPIO pins : PIN_LED_HEARTBEAT
	GPIO_InitStruct.GPIOx				= PORT_LED_HEARTBEAT;
	GPIO_InitStruct.Pin					= PIN_LED_HEARTBEAT;
	GPIO_InitStruct.Mode				= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull				= GPIO_PULLDOWN;
	GPIO_InitStruct.Speed				= GPIO_SPEED_VERY_HIGH;
	GPIO_init(&GPIO_InitStruct);

	// Configure GPIO pin Output Level
	GPIO_resetBits(PORT_LED_HEARTBEAT, PIN_LED_HEARTBEAT);
}

/**
  * @brief  FreeRTOS initialization for heartbeat module
  * @param  None
  * @retval None
  */
void HEARTBEAT_freeRtosInit(void)
{
	// Create the thread(s)
	// definition and creation of HeartbeatTask
	osThreadDef(Heartbeat, heartbeatTask, osPriorityLow, 0, 128);
	heartbeatHandle = osThreadCreate(osThread(Heartbeat), NULL);
}
