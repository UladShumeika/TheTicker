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
// Static function prototypes
//---------------------------------------------------------------------------
static void SPI_gpioInitPins(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

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
 * @brief	This function initializes the GPIO peripheral to be used with the selected SPI
 * @note	Default GPIO parameters:
 * 			Function mode - alternate function mode;
 * 			Speed mode - High speed mode;
 * 			Output mode - Output push-pull;
 * 			Resistor configuration - No pull
 * @param	GPIOx: A pointer to GPIOx peripheral to be used where x is between A to F
 * @param	GPIO_Pin: Specifies the GPIO pins to be configured. This parameter can be any value of 
 * 					  @ref GPIO_pins_define
 * @retval	None
*/
static void SPI_gpioInitPins(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint32_t pinPos = 0x00, pos = 0x00 , currentPin = 0x00;

	// Check the parameters

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
      		//GPIOx->PUPDR |= (((uint32_t)SPI_GPIO_PuPd_NOPULL) << (pinPos * 2));
		}
	}
}
