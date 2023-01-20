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
#include <ush_spi.h>

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static uint16_t SPI_GPIO_GetPortSource(GPIO_TypeDef* GPIOx);
static void SPI_GPIO_EnableClock(GPIO_TypeDef* GPIOx);

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes the SPIx peripheral according to the specified parameters in the USH_SPI_initDefaultTypeDef.
 * @note 	This function has default settings:
 *			- Master mode selected;
 *			- Full duplex selected;
 *			- 16bits data size selected;
 *			- Chip select pin software control selected;
 *			- MSB transmitted first;
 *			- CRC calculation disabled;
 *			- TI mode disable.
 * @param 	initStructure - a pointer to a USH_SPI_initDefaultTypeDef structure that contains the configuration
 * 							information for the specified SPI peripheral.
 * @retval	None.
 */
void SPI_init(USH_SPI_initDefaultTypeDef *initStructure)
{
	uint16_t temp;

	// Check parameters
	assert_param(IS_SPI_ALL_INSTANCE(initStructure->SPIx));
	assert_param(IS_SPI_PINSPACK(initStructure->PinsPack));
	assert_param(IS_SPI_BAUDRATE_PRESCALER(initStructure->BaudRatePrescaler));
	assert_param(IS_SPI_MODE(initStructure->Mode));

	/* ----------------------- GPIO configuration-------------------------- */




	/* ----------------------- SPI configuration--------------------------- */

	// Setting the default settings for CR1 register
	temp = initStructure->SPIx->CR1;
	temp |= (SPI_MASTER | SPI_DATASIZE | SPI_NSS);
	temp &= ~(SPI_DIRECTION_2LINES | SPI_FIRST_BIT | SPI_CRC_CALCULATION);

	// Setting the settings from structure
	temp &= ~(SPI_BAUDRATE_MASK | SPI_MODE_MASK);
	temp |= (initStructure->BaudRatePrescaler | initStructure->Mode);
	initStructure->SPIx->CR1 = temp;

	// Setting the default settings for CR2 register
	temp = initStructure->SPIx->CR2;
	temp &= ~(SPI_TI_MODE);
	initStructure->SPIx->CR2 = temp;
}


//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

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
