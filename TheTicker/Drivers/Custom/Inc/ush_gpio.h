//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_GRIO_H
#define __USH_GRIO_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
 * @brief GPIO pins enumeration
 */
typedef enum
{
	GPIO_PIN_0		= 0x0001U,		/* Pin 0 selected */
	GPIO_PIN_1		= 0x0002U,		/* Pin 1 selected */
	GPIO_PIN_2		= 0x0004U,		/* Pin 2 selected */
	GPIO_PIN_3 		= 0x0008U,		/* Pin 3 selected */
	GPIO_PIN_4		= 0x0010U,		/* Pin 4 selected */
	GPIO_PIN_5		= 0x0020U,		/* Pin 5 selected */
	GPIO_PIN_6		= 0x0040U,		/* Pin 6 selected */
	GPIO_PIN_7		= 0x0080U,		/* Pin 7 selected */
	GPIO_PIN_8		= 0x0100U,		/* Pin 8 selected */
	GPIO_PIN_9		= 0x0200U,		/* Pin 9 selected */
	GPIO_PIN_10		= 0x0400U,		/* Pin 10 selected */
	GPIO_PIN_11		= 0x0800U,		/* Pin 11 selected */
	GPIO_PIN_12		= 0x1000U,		/* Pin 12 selected */
	GPIO_PIN_13		= 0x2000U,		/* Pin 13 selected */
	GPIO_PIN_14		= 0x4000U,		/* Pin 14 selected */
	GPIO_PIN_15		= 0x8000U,		/* Pin 15 selected */
	GPIO_PIN_FULL	= 0xFFFFU		/* All pins selected */
} USH_GPIO_pins;

/**
 * @brief GPIO mode enumeration
 */
typedef enum
{
	GPIO_MODE_INPUT				= 0x00UL,		/* GPIO input mode */
	GPIO_MODE_OUTPUT_PP			= 0x01UL,		/* GPIO output push pull mode */
	GPIO_MODE_OUTPUT_OD			= 0x11UL,		/* GPIO output open drain mode */
	GPIO_MODE_ALTERNATE_PP		= 0x02UL,		/* GPIO alternate function push pull mode */
	GPIO_MODE_ALTERNATE_OD		= 0x12UL,		/* GPIO alternate function open drain mode */
	GPIO_MODE_ANALOG			= 0x03UL		/* GPIO analog mode */
} USH_GPIO_modes;

/**
 * @brief GPIO pull enumeration
 */
typedef enum
{
	GPIO_NOPULL		= 0x00UL,		/* No pull up and pull down */
	GPIO_PULLUP		= 0x01UL,		/* Pull up selected */
	GPIO_PULLDOWN	= 0x02UL		/* Pull down selected */
} USH_GPIO_pull;

/**
 * @brief GPIO speed enumeration
 */
typedef enum
{
	GPIO_SPEED_LOW			= 0x00UL,		/* Low speed mode selected */
	GPIO_SPEED_MEDIUM		= 0x01UL,		/* Medium speed mode selected */
	GPIO_SPEED_HIGH			= 0x02UL,		/* High speed mode selected */
	GPIO_SPEED_VERY_HIGH	= 0x03UL		/* Very high speed mode selected */
} USH_GPIO_speed;

/**
 * @brief GPIO alternate function enumeration
 */
typedef enum
{
	GPIO_AF5_SPI1 		= 0x05UL,		/* SPI1/I2S1 alternate function mapping */
	GPIO_AF5_SPI2 		= 0x05UL,		/* SPI2/I2S2 alternate function mapping */
	GPIO_AF5_SPI4 		= 0x05UL,		/* SPI4/I2S4 alternate function mapping */
	GPIO_AF5_SPI5 		= 0x05UL,		/* SPI5 alternate function mapping */
	GPIO_AF5_SPI6 		= 0x05UL,		/* SPI6 alternate function mapping */

	GPIO_AF6_SPI3		= 0x06UL,		/* SPI3/I2S3 alternate function mapping */

	GPIO_AF7_USART1		= 0x07UL,		/* USART1 alternative function mapping */
	GPIO_AF7_USART2		= 0x07UL,		/* USART2 alternative function mapping */
	GPIO_AF7_USART3		= 0x07UL,		/* USART3 alternative function mapping */

	GPIO_AF8_UART4		= 0x07UL,		/* UART4 alternative function mapping */
	GPIO_AF8_UART5		= 0x07UL,		/* UART5 alternative function mapping */
	GPIO_AF8_USART6		= 0x07UL,		/* USART6 alternative function mapping */
	GPIO_AF8_UART7		= 0x07UL,		/* UART7 alternative function mapping */
	GPIO_AF8_UART8		= 0x07UL		/* UART8 alternative function mapping */
} USH_GPIO_alternate;

/**
  * @brief GPIO init structure definition
  */
typedef struct
{
	GPIO_TypeDef *GPIOx;		/* A pointer to GPIOx peripheral to be used where x is between A to F */

	USH_GPIO_pins Pin;       	/* The GPIO pins to be configured.
	                           	   This parameter can be any value of @ref USH_GPIO_pins */

	uint32_t Mode;      		/* The operating mode for the selected pins.
	                           	   This parameter can be a value of @ref USH_GPIO_modes */

	uint32_t Pull;      		/* The Pull-up or Pull-Down activation for the selected pins.
	                           	   This parameter can be a value of @ref USH_GPIO_pull */

	uint32_t Speed;     		/* The speed for the selected pins.
	                           	   This parameter can be a value of @ref USH_GPIO_speed */

	uint32_t Alternate;  		/* Peripheral to be connected to the selected pins.
	                               This parameter can be a value of @ref USH_GPIO_alternate */
} USH_GPIO_initTypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET
} USH_GPIO_pinState;

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------

#define GPIO_PIN_MASK              		((uint32_t)0x0000FFFF) 	/* PIN mask for assert test */
#define IS_GPIO_PIN(PIN)           		(((PIN) & GPIO_PIN_MASK ) != (uint32_t)0x00)

#define IS_GPIO_MODE(MODE)		   		(((MODE) == GPIO_MODE_INPUT)     	| \
										 ((MODE) == GPIO_MODE_OUTPUT_PP)    | \
										 ((MODE) == GPIO_MODE_OUTPUT_OD)    | \
										 ((MODE) == GPIO_MODE_ALTERNATE_PP) | \
										 ((MODE) == GPIO_MODE_ALTERNATE_OD) | \
										 ((MODE) == GPIO_MODE_ANALOG))

#define IS_GPIO_PULL(PULL)		   		(((PULL) == GPIO_NOPULL) | \
										 ((PULL) == GPIO_PULLUP) | \
										 ((PULL) == GPIO_PULLDOWN))

#define IS_GPIO_SPEED(SPEED)	   		(((SPEED) == GPIO_SPEED_LOW)    | \
								    	 ((SPEED) == GPIO_SPEED_MEDIUM) | \
										 ((SPEED) == GPIO_SPEED_HIGH)   | \
								    	 ((SPEED) == GPIO_SPEED_VERY_HIGH))

#define IS_GPIO_ALTERNATE(ALTERNATE)	(((ALTERNATE) == GPIO_Af5_SPI1) | \
										 ((ALTERNATE) == GPIO_Af5_SPI2) | \
										 ((ALTERNATE) == GPIO_Af5_SPI4) | \
										 ((ALTERNATE) == GPIO_Af5_SPI5) | \
										 ((ALTERNATE) == GPIO_Af5_SPI6) | \
										 ((ALTERNATE) == GPIO_Af6_SPI3))

#define IS_GPIO_STATE(STATE)			(((STATE) == GPIO_PIN_RESET) | \
										 ((STATE) == GPIO_PIN_SET))

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes the GPIOx peripheral according to the specified parameters in the USH_GPIO_initTypeDef.
 * @param 	initStructure - a pointer to a USH_GPIO_initTypeDef structure that contains the configuration information
 * 						    for the specified GPIO peripheral.
 * @retval	None
 */
void GPIO_init(USH_GPIO_initTypeDef *initStructure);

/**
 * @brief	This function clears the selected data port bits.
 * @note	This function uses GPIOx_BSRR register to allow atomic read/modify accesses. In this way,
 * 			there is no risk of an IRQ occurring between the read and the modify access.
 * @param 	GPIOx - A pointer to GPIOx peripheral to be used where x is between A to F.
 * @param 	gpioPins - The GPIO pins to be configured. This parameter can be any value of @ref USH_GPIO_pins.
 * @retval	None.
 */
void GPIO_resetBits(GPIO_TypeDef *GPIOx, uint16_t gpioPins);

/**
 * @brief 	This function toggles the specified GPIO pins.
 * @param 	GPIOx - A pointer to GPIOx peripheral to be used where x is between A to F.
 * @param  	gpioPins - The GPIO pins to be configured. This parameter can be any value of @ref USH_GPIO_pins.
 * @retval	None.
 */
void GPIO_toggleBits(GPIO_TypeDef* GPIOx, uint16_t gpioPins);

#endif /* __USH_GRIO_H */
