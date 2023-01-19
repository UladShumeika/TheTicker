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
// Includes
//---------------------------------------------------------------------------
#include "custom_stm32f429_spi.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

// SPI default setting
#define SPI_Direction_2Lines_FullDuplex		((uint16_t)0x0000)
#define SPI_Mode_Master						((uint16_t)0x0104)
#define SPI_DataSize_16b					((uint16_t)0x0800)
#define SPI_NSS_Soft						((uint16_t)0x0200)
#define SPI_FirstBit_MSB					((uint16_t)0x0000)
#define SPI_CRCPolynomial					((uint16_t)0x0000)

#define GPIO_NUMBER           				16U

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3) || \
                                   ((PERIPH) == SPI4) || \
                                   ((PERIPH) == SPI5) || \
                                   ((PERIPH) == SPI6))

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static void SPI_gpioInitPins(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_AF);
static uint16_t SPI_GPIO_GetPortSource(GPIO_TypeDef* GPIOx);
static void SPI_GPIO_EnableClock(GPIO_TypeDef* GPIOx);

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief  Initializes SPIx peripheral with custom pinspack and default other settings
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  pinspack: Pinspack you will use from default SPI table. This parameter can be a value of
 * 					 @ref CUS_SPI_PinsPack_t enumeration
 * @retval None
 */
// void CUS_spiInit(SPI_TypeDef* SPIx, CUS_SPI_PinsPack_t pinspack)
// {

// }

/**
 * @brief	This function enables clock for the selected port
 * @param 	*GPIOx: A pointer to GPIOx peripheral to be used where x is between A to F
 * @retval	None
 */
static void SPI_GPIO_EnableClock(GPIO_TypeDef* GPIOx)
{
	RCC->AHB1ENR |= (1 << SPI_GPIO_GetPortSource(GPIOx));
}

/**
 * @brief	This function returns port source number (0 - GPIOA; 1 - GPIOB; 2 - GPIOC and so on. For example see RCC_AHB1LPENR register)
 * @param	*GPIOx: A pointer to GPIOx peripheral to be used where x is between A to F
 * @retval	Return port source number (0 - GPIOA; 1 - GPIOB; 2 - GPIOC and so on. For example see RCC_AHB1LPENR register)
 */
static uint16_t SPI_GPIO_GetPortSource(GPIO_TypeDef* GPIOx)
{
	// Get port source number
	// Offset from GPIOA
	return ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)); // Difference between 2 GPIO addresses
}

/**
 * @brief	This function initializes the GPIO peripheral to be used with the selected SPI
 * @note	Default GPIO parameters:
 * 			Function mode - alternate function mode;
 * 			Speed mode - High speed mode;
 * 			Output mode - Output push-pull;
 * 			Resistor configuration - No pull
 * @param	GPIOx: A pointer to GPIOx peripheral to be used where x is between A to F
 * @param	GPIO_Pin: Specifies the GPIO pins to be configured. This parameter can be any value of @ref GPIO_pins_define
 * @retval	None
*/
static void SPI_gpioInitPins(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_AF)
{
	uint32_t pinPos = 0x00, pos = 0x00 , currentPin = 0x00;
	uint32_t temp;

	// Check the parameters

	// Enable clock port
	SPI_GPIO_EnableClock(GPIOx);

	for (pinPos = 0x00; pinPos < 0x10; pinPos++) // 0x10 -> 16 ()
	{	
		// Get the port pins position 
		pos = ((uint32_t)0x01) << pinPos;
		currentPin = GPIO_Pin & pos;

		if(currentPin == pos)
		{	
			// Enable alternate function mode
			GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinPos * 2));
      		GPIOx->MODER |= (((uint32_t)SPI_GPIO_Mode_AF) << (pinPos * 2));

        	// Speed mode configuration
        	GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinPos * 2));
        	GPIOx->OSPEEDR |= ((uint32_t)(SPI_GPIO_High_Speed) << (pinPos * 2));

        	// Output mode configuration
        	GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinPos)) ;
        	GPIOx->OTYPER |= (uint16_t)(((uint16_t)SPI_GPIO_OType_PP) << ((uint16_t)pinPos));

			// Pull-up pull-down resistor configuration
      		GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinPos * 2));
      		GPIOx->PUPDR |= (((uint32_t)SPI_GPIO_PuPd_NOPULL) << (pinPos * 2));

      		// Set alternate function
      		GPIOx->AFR[pinPos >> 0x03] &= ~((pinPos & (uint32_t)0x07) * 4);
      		temp = (uint32_t)GPIO_AF << ((pinPos & (uint32_t)0x07) * 4);
      		GPIOx->AFR[pinPos >> 0x03] |= temp;
		}
	}
}
