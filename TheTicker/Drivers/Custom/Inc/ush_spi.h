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
									   This parameter can be a value of @ref USH_SPI_pinsPack */

	uint16_t BaudRatePrescaler;		/* The Baud Rate prescaler value which will be used to configure the transmit
									   and receive SCK clock. This parameter can be a value of @ref USH_SPI_baudRatePrescaler */

	uint16_t Mode;       			/* SPI modes selection. This parameter can be a value of @ref USH_SPI_mode */

} USH_SPI_initDefaultTypeDef;

/**
 * @brief SPI pinsPack enumeration to select pins combination for SPI
 */
typedef enum
{
	SPI_PINSPACK_1	= 0x00U,	/* pinsPack1 selected */
	SPI_PINSPACK_2	= 0x01U		/* pinsPack2 selected */
} USH_SPI_pinsPack;

/**
 * @brief SPI baudrate prescaler enumeration
 */
typedef enum
{
	SPI_BAUDRATE_PRESCALER_2		= 0x0000U,		/* f_pclk/2 selected */
	SPI_BAUDRATE_PRESCALER_4		= 0x0008U,		/* f_pclk/4 selected */
	SPI_BAUDRATE_PRESCALER_8		= 0x0010U,		/* f_pclk/8 selected */
	SPI_BAUDRATE_PRESCALER_16		= 0x0018U,		/* f_pclk/16 selected */
	SPI_BAUDRATE_PRESCALER_32		= 0x0020U,		/* f_pclk/32 selected */
	SPI_BAUDRATE_PRESCALER_64		= 0x0028U,		/* f_pclk/64 selected */
	SPI_BAUDRATE_PRESCALER_128		= 0x0030U,		/* f_pclk/128 selected */
	SPI_BAUDRATE_PRESCALER_256		= 0x0038U		/* f_pclk/256 selected */
} USH_SPI_baudRatePrescaler;

/**
 * @brief SPI modes selection enumeration
 */
typedef enum
{
	SPI_MODE_1	= 0x0000U,		/* Clock polarity low, clock phase 1st edge */
	SPI_MODE_2	= 0x0010U, 		/* Clock polarity low, clock phase 2nd edge */
	SPI_MODE_3	= 0x0001U, 		/* Clock polarity high, clock phase 1st edge */
	SPI_MODE_4  = 0x0011U 		/* Clock polarity high, clock phase 2nd edge */
} USH_SPI_mode;




















//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void SPI_init(SPI_initTypeDef* SPI_initStruct);

#endif /* __USH_SPI_H */
