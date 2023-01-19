/**
  ******************************************************************************
  * @file    custom_stm32f429_spi.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    16-January-2023
  * @brief   This file contains all the functions prototypes for the SPI firmware
  *          library.  
  ******************************************************************************
  */
  
//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __CUSTOM_SPI_H
#define __CUSTOM_SPI_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
  * @brief SPI init structure definition
  */
typedef struct
{
	SPI_TypeDef* SPIx;				// A pointer to SPIx peripheral to be used where x is between 1 to 6

	uint8_t pinsPack;				// SPI pinsPack enumeration to select pins combination for SPI.
									// This parameter can be a value of @ref SPI_pinsPack_t

	uint16_t baudRatePrescaler;		// The Baud Rate prescaler value which will be used to configure the transmit
									// and receive SCK clock. This parameter can be a value of @ref SPI_baudRatePrescaler_t

	uint16_t SPI_mode;       		// SPI modes selection. This parameter can be a value of @ref SPI_mode_t

} SPI_initTypeDef;

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

/**
 * @brief  SPI pinsPack enumeration to select pins combination for SPI
 */
typedef enum 
{
	SPI_pinsPack_1	= 0x00,		// select PinsPack1 from Pinout table for specific SPI
	SPI_pinsPack_2	= 0x01		// select PinsPack2 from Pinout table for specific SPI
} SPI_pinsPack_t;

/** 
  * @brief  GPIO configuration mode enumeration 
  */   
typedef enum
{ 
	SPI_GPIO_Mode_IN	= 0x00,		// GPIO input mode
	SPI_GPIO_Mode_OUT	= 0x01,  	// GPIO output mode
	SPI_GPIO_Mode_AF	= 0x02,  	// GPIO alternate function mode
	SPI_GPIO_Mode_AN	= 0x03   	// GPIO analog mode
} SPI_GPIOMode_TypeDef;

/** 
  * @brief  GPIO output maximum frequency enumeration
  */  
typedef enum
{ 
	SPI_GPIO_Low_Speed		= 0x00,		// low speed
	SPI_GPIO_Medium_Speed	= 0x01, 	// medium speed
	SPI_GPIO_Fast_Speed		= 0x02, 	// fast speed
	SPI_GPIO_High_Speed		= 0x03  	// high speed
} SPI_GPIOSpeed_TypeDef;

/**
  * @brief  GPIO output type enumeration
  */
typedef enum
{
	SPI_GPIO_OType_PP	= 0x00,		// push-pull
	SPI_GPIO_OType_OD 	= 0x01		// open-drain
} SPI_GPIOOType_TypeDef;

/**
  * @brief  GPIO configuration pull-up pull-down enumeration
  */
typedef enum
{
	SPI_GPIO_PuPd_NOPULL 	= 0x00,		// no pull
	SPI_GPIO_PuPd_UP		= 0x01,		// pull-up
	SPI_GPIO_PuPd_DOWN		= 0x02		// pull-down
} SPI_GPIOPuPd_TypeDef;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void SPI_init(SPI_initTypeDef SPI_initStruct);

#endif /* __CUSTOM_SPI_H */
