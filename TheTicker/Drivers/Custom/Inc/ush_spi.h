/**
  ******************************************************************************
  * @file    ush_spi.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    16-January-2023
  * @brief   This file contains the functions prototypes for the SPI firmware
  *          library.  
  ******************************************************************************
  */
  
//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_SPI_H
#define __USH_SPI_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "ush_gpio.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
  * @brief SPI init structure definition with default settings
  */
typedef struct
{
	SPI_TypeDef* SPIx;				/* A pointer to SPIx peripheral to be used where x is between 1 to 6 */

	uint8_t PinsPack;				/* SPI pinsPack enumeration to select pins combination for SPI.
									   This parameter can be a value of @ref SPI_pinsPack_t */

	uint16_t BaudRatePrescaler;		/* The Baud Rate prescaler value which will be used to configure the transmit
									   and receive SCK clock. This parameter can be a value of @ref SPI_baudRatePrescaler_t */

	uint16_t Mode;       			/* SPI modes selection. This parameter can be a value of @ref SPI_mode_t */

} USH_SPI_initDefaultTypeDef;

/**
 * @brief SPI pinsPack enumeration to select pins combination for SPI
 */
typedef enum
{
	SPI_PINSPACK_1	= 0x00,		/* pinsPack1 selected */
	SPI_PINSPACK_2	= 0x01		/* pinsPack2 selected */
} USH_SPI_pinsPack;












/**
 * @brief	SPI baudrate prescaler enumeration
 */
typedef enum
{
	SPI_BaudRatePrescaler_2		= 0x0000,
	SPI_BaudRatePrescaler_4		= 0x0008,
	SPI_BaudRatePrescaler_8		= 0x0010,
	SPI_BaudRatePrescaler_16	= 0x0018,
	SPI_BaudRatePrescaler_32	= 0x0020,
	SPI_BaudRatePrescaler_64	= 0x0028,
	SPI_BaudRatePrescaler_128	= 0x0030,
	SPI_BaudRatePrescaler_256	= 0x0038
} SPI_baudRatePrescaler_t;

/**
 * @brief  SPI modes selection enumeration
 */
typedef enum
{
	SPI_Mode_0	= 0x0000,		// clock polarity low, clock phase 1st edge
	SPI_Mode_1	= 0x0010, 		// clock polarity low, clock phase 2nd edge
	SPI_Mode_2	= 0x0001, 		// clock polarity high, clock phase 1st edge
	SPI_Mode_3  = 0x0011 		// clock polarity high, clock phase 2nd edge
} SPI_mode_t;









//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void SPI_init(SPI_initTypeDef* SPI_initStruct);

#endif /* __USH_SPI_H */
