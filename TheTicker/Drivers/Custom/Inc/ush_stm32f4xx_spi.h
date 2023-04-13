/**
  ******************************************************************************
  * @file    ush_stm32f4xx_spi.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    16-January-2023
  * @brief   Header file of SPI module.
  *
  ******************************************************************************
  */
  
/* NOTE: The work with DMA is not implemented */

/* The SPI setting is based on the choice of a set of pins and a set of DMA.
 *
 * The set of pins.
 * 		  |             pinsPack_1			|			  pinsPack_2		  |
 * SPIx___|__MOSI__|__MISO__|__CLK__|__NSS__|__MOSI__|__MISO__|__CLK__|__NSS__|
 * 		  |		   |		|		|		|		 |		  |		  |       |
 * SPI1	  |  PA7   |  PA6   |  PA5  |  PA4  |  PB5	 |  PB4   |	 PB3  |  PA15 |
 * SPI2	  |	 PC3   |  PC2	|  PB10 |  PB9	|  PB15	 |  PB14  |	 PB13 |  PB12 |
 * SPI3	  |	 PB5   |  PB4	|  PB3  |  PB4	|  PC12  |  PC11  |	 PC10 |	 PA15 |
 * SPI4	  |	 PE6   |  PE5	|  PE2  |  PE4	|  PE14  |	PE13  |  PE12 |  PE11 |
 * SPI5	  |	 PF9   |  PF8	|  PF7  |  PF6	|   --   |   --   |   --  |   --  |
 * SPI6	  |	 PG14  |  PG12	|  PG13 |  PG8  |	--   |   --   |   --  |   --  |
 *
 * The set of DMA.
 *     	   |		 dmaPack_1	     |		   dmaPack_2       |
 * SPIx____|_DMAx Stream x Channel x_|_DMAx Stream x Channel x_|
 * 		   |			             |				           |
 * SPI1_RX |      DMA2 St.0 Ch.3     |      DMA2 St.2 Ch.3     |
 * SPI1_TX |      DMA2 St.3 Ch.3     |      DMA2 St.5 Ch.3     |
 * 		   |						 |						   |
 * SPI2_RX |      DMA1 St.3 Ch.0     |			 ----		   |
 * SPI2_TX |      DMA1 St.4 Ch.0     |			 ----		   |
 * 		   |						 |						   |
 * SPI3_RX |      DMA1 St.0 Ch.0     |      DMA1 St.2 Ch.0     |
 * SPI3_TX |      DMA1 St.5 Ch.0     |      DMA1 St.7 Ch.0     |
 * 		   |						 |						   |
 * SPI4_RX |      DMA2 St.0 Ch.4     |      DMA2 St.3 Ch.5     |
 * SPI4_TX |      DMA2 St.1 Ch.4     |      DMA2 St.4 Ch.5     |
 * 		   |						 |						   |
 * SPI5_RX | 	  DMA2 St.3 Ch.2     |      DMA2 St.5 Ch.7     |
 * SPI5_TX |      DMA2 St.4 Ch.2     | 		DMA2 St.6 Ch.7     |
 * 		   |						 |						   |
 * SPI6_RX | 	  DMA2 St.6 Ch.1     |		     ----		   |
 * SPI6_TX | 	  DMA2 St.5 Ch.1     |			 ----		   |
 *
 */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_SPI_H
#define __USH_STM32F4XX_SPI_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_gpio.h"
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

/**
  * @brief  GPIO output type enumeration
  */
typedef enum
{
	SPI_GPIO_OType_PP	= 0x00,		// push-pull
	SPI_GPIO_OType_OD 	= 0x01		// open-drain
} SPI_GPIOOType_TypeDef;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

#endif /* __USH_STM32F4XX_SPI_H */
