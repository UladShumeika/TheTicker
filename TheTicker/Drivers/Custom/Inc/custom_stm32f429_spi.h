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

#endif /* __CUSTOM_SPI_H */
