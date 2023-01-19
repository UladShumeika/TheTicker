//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_gpio.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
  * @brief GPIO init structure definition
  */
typedef struct
{
	GPIO_TypeDef *GPIOx;		/* A pointer to GPIOx peripheral to be used where x is between A to F */

	uint32_t Pin;       		/* The GPIO pins to be configured.
	                           	   This parameter can be any value of @ref USH_GPIO_pins */

	uint32_t Mode;      		/* The operating mode for the selected pins.
	                           	   This parameter can be a value of @ref USH_GPIO_modes */

	uint32_t Pull;      		/* The Pull-up or Pull-Down activation for the selected pins.
	                           	   This parameter can be a value of @ref USH_GPIO_pull */

	uint32_t Speed;     		/* The speed for the selected pins.
	                           	   This parameter can be a value of @ref GPIO_speed_define */

	uint32_t Alternate;  		/* Peripheral to be connected to the selected pins.
	                               This parameter can be a value of @ref GPIO_Alternate_function_selection */
} USH_GPIO_initTypeDef;

/**
 * @brief GPIO pins enumeration
 */
typedef enum
{
	GPIO_PIN_0		= 0x0001,
	GPIO_PIN_1		= 0x0002,
	GPIO_PIN_2		= 0x0004,
	GPIO_PIN_3 		= 0x0008,
	GPIO_PIN_4		= 0x0010,
	GPIO_PIN_5		= 0x0020,
	GPIO_PIN_6		= 0x0040,
	GPIO_PIN_7		= 0x0080,
	GPIO_PIN_8		= 0x0100,
	GPIO_PIN_9		= 0x0200,
	GPIO_PIN_10		= 0x0400,
	GPIO_PIN_11		= 0x0800,
	GPIO_PIN_12		= 0x1000,
	GPIO_PIN_13		= 0x2000,
	GPIO_PIN_14		= 0x4000,
	GPIO_PIN_15		= 0x8000,
	GPIO_PIN_FULL	= 0xFFFF
} USH_GPIO_pins;

/**
 * @brief GPIO mode enumeration
 */
typedef enum
{
	GPIO_MODE_INPUT			= 0x00UL,
	GPIO_MODE_OUTPUT		= 0x01UL,
	GPIO_MODE_ALTERNATE		= 0x10UL,
	GPIO_MODE_ANALOG		= 0x11UL
} USH_GPIO_modes;

/**
 * @brief GPIO pull enumeration
 */
typedef enum
{
	GPIO_NOPULL			= 0x00UL,
	GPIO_PULLUP			= 0x01UL,
	GPIO_PULLDOWN		= 0x10UL
} USH_GPIO_pull;




