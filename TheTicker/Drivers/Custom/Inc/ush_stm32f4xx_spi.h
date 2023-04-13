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
	SPI_BAUDRATE_PRESCALER_256		= 0x0038U,		/* f_pclk/256 selected */
	SPI_BAUDRATE_MASK				= 0x0038U
} USH_SPI_baudRatePrescaler;

/**
 * @brief SPI modes selection enumeration
 */
typedef enum
{
	SPI_MODE_1		= 0x00U,		/* Clock polarity low, clock phase 1st edge */
	SPI_MODE_2		= 0x02U, 		/* Clock polarity low, clock phase 2nd edge */
	SPI_MODE_3		= 0x01U, 		/* Clock polarity high, clock phase 1st edge */
	SPI_MODE_4  	= 0x03U, 		/* Clock polarity high, clock phase 2nd edge */
	SPI_MODE_MASK 	= 0x03U
} USH_SPI_mode;

/**
 * @brief SPI frame format selection enumeration
 */
typedef enum
{
	SPI_MSB_FIRST		  = 0x00U,		/* MSB transmitted first *//**< SPI_MSB_FIRST */
	SPI_LSB_FIRST		  = 0x80U,		/* LSB transmitted first *//**< SPI_LSB_FIRST */
	SPI_FRAME_FORMAT_MASK = 0x80U
} USH_SPI_frameFormat;

/**
  * @brief SPI init structure definition with default settings
  */
typedef struct
{
	SPI_TypeDef* SPIx;								/* A pointer to SPIx peripheral to be used where x is between 1 to 6 */

	USH_SPI_pinsPack PinsPack;						/* SPI pinsPack enumeration to select pins combination for SPI.
									   	   	   	   	   This parameter can be a value of @ref USH_SPI_pinsPack */

	USH_SPI_baudRatePrescaler BaudRatePrescaler;	/* The Baud Rate prescaler value which will be used to configure the transmit
									   	   	   	   	   and receive SCK clock. This parameter can be a value of @ref USH_SPI_baudRatePrescaler */

	USH_SPI_mode Mode;       						/* SPI modes selection. This parameter can be a value of @ref USH_SPI_mode */

	USH_SPI_frameFormat FrameFormat;				/* SPI frame format selection. This parameter can be a value of @ref USH_SPI_frameFormat */

} USH_SPI_initDefaultTypeDef;

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
