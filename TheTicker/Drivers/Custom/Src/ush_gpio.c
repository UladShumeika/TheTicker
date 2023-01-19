//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_gpio.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
  * @brief GPIO Init structure definition
  */
typedef struct
{
	GPIO_TypeDef *GPIOx;		/* A pointer to GPIOx peripheral to be used where x is between A to F */

	uint32_t Pin;       		/* The GPIO pins to be configured.
	                           	   This parameter can be any value of @ref GPIO_pins_define */

	uint32_t Mode;      		/* The operating mode for the selected pins.
	                           	   This parameter can be a value of @ref GPIO_mode_define */

	uint32_t Pull;      		/* The Pull-up or Pull-Down activation for the selected pins.
	                           	   This parameter can be a value of @ref GPIO_pull_define */

	uint32_t Speed;     		/* The speed for the selected pins.
	                           	   This parameter can be a value of @ref GPIO_speed_define */

	uint32_t Alternate;  		/* Peripheral to be connected to the selected pins.
	                               This parameter can be a value of @ref GPIO_Alternate_function_selection */
} USH_GPIO_initTypeDef;
