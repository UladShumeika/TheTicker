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

#endif /* __CUSTOM_SPI_H */
