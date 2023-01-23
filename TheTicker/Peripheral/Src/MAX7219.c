//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "MAX7219.h"

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
 * @brief	This function initializes MAX7219.
 * @retval	None.
 */
void MAX7219_init(void)
{
	USH_SPI_initDefaultTypeDef initStructure = {0,};

	initStructure.SPIx 					= SPI1;
	initStructure.PinsPack 				= SPI_PINSPACK_1;
	initStructure.BaudRatePrescaler		= SPI_BAUDRATE_PRESCALER_16;
	initStructure.Mode 					= SPI_MODE_1;
	SPI_init(&initStructure);

	MAX7219_state(ALL_DIGITS, NORMAL_MODE);
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief This function sets the decoding mode for the driver
 *
 */
void MAX7219_decodeMode(USH_MAX7219_digits digit, USH_MAX7219_REG_DECODE_MODE mode)
{
	MAX7219_sendDataWithLatch(digit, REG_DECODE_MODE, mode);
}

/**
  * @brief  This function enables or disables a matrix driver.
  * @param  digit - The digit indicates which digit of the matrix driver to transfer data to.
  * 				This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  mode - The driver mode. This parameter can be any value of @ref USH_MAX7219_REG_SHUTDOWN.
  * @retval None.
  */
void MAX7219_state(USH_MAX7219_digits digit, USH_MAX7219_REG_SHUTDOWN mode)
{
	MAX7219_sendDataWithLatch(digit, REG_SHUTDOWN, mode);
}

/**
  * @brief  This function sends data WITH a latch.
  * @param  digit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithLatch(USH_MAX7219_digits digit, USH_MAX7219_registers reg, uint8_t data)
{
	SPI_csPin(LOW);
	MAX7219_sendDataWithoutLatch(digit, reg, data);
	SPI_csPin(HIGH);
}

/**
  * @brief  This function sends data WITHOUT a latch.
  * @param	digit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * 			  This parameter can be any value of @ref USH_MAX7219_registers.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithoutLatch(USH_MAX7219_digits digit, USH_MAX7219_registers reg, uint8_t data)
{
	uint8_t NoOp = 0;

	for(uint8_t i = 1; i <= MATRIX_NUM; i++)
	{
		if(digit == ALL_DIGITS)
		{
			SPI_writeData(SPI1, reg, data);
		} else
		{
			if(i == digit)
			{
				SPI_writeData(SPI1, reg, data);
			} else
			{
				SPI_writeData(SPI1, NoOp, NoOp);
			}
		}
	}
}
