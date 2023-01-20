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
 *
 *
 * @param 	initStructure
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
 * @brief  Initializes SPIx peripheral with custom pinspack and default other settings
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  pinspack: Pinspack you will use from default SPI table. This parameter can be a value of
 * 					 @ref CUS_SPI_PinsPack_t enumeration
 * @retval None
 */
void SPI_init(SPI_initTypeDef* SPI_initStruct)
{
	uint16_t tmprgr, pins;

	// Check the parameters
	assert_param(IS_SPI_ALL_PERIPH(SPI_initStruct->SPIx));
	assert_param(IS_SPI_PINSPACK(SPI_initStruct->pinsPack));
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_initStruct->baudRatePrescaler));
	assert_param(IS_SPI_MODE(SPI_initStruct->SPI_mode));

	if(SPI_initStruct->SPIx == SPI1)
	{
		// Enable SPI1 clock
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

		if(SPI_initStruct->pinsPack == SPI_pinsPack_1)
		{
//			pins = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//			SPI_gpioInitPins(GPIOA, pins, GPIO_AF_SPI1);
		}
	}



//	if(SPIx == SPI1)
//	{
//
//
//		if(pinsPack == SPI_pinsPack_1)
//		{
//
//		} else		// SPI_pinsPack_2
//		{
//			pins = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//			SPI_gpioInitPins(GPIOB, pins, GPIO_AF_SPI1);
//		}

//	}
}

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
