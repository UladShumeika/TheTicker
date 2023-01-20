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
static void SPI_gpioInitPins(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_AF);
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
	temp |= (SPI_MASTER | SPI_DIRECTION_2LINES | SPI_DATASIZE | SPI_NSS | SPI_FIRST_BIT | SPI_CRC_CALCULATION);

	// Setting the settings from structure
	temp |= (initStructure->BaudRatePrescaler | initStructure->Mode);
	initStructure->SPIx->CR1 = temp;

	// Setting the default settings for CR2 register
	temp = initStructure->SPIx->CR2;
	temp |= (SPI_TI_MODE);
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
