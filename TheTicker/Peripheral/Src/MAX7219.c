//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "MAX7219.h"
#include "cmsis_os.h"

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
	MAX7219_decodeMode(ALL_DIGITS, NO_DECODE_FOR_ALL);
	MAX7219_intensity(ALL_DIGITS, INTENSITY_13_32);
	MAX7219_scanLimit(ALL_DIGITS, SCAN_LIMIT_0_7);
	MAX7219_clean(ALL_DIGITS);

}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function cleans matrix's digits.
 * @param 	digit - The digit indicates which digit of the matrix driver to transfer data to.
 * 					This parameter can be any value of @ref USH_MAX7219_digits.
 * @retval	None.
 */
void MAX7219_clean(USH_MAX7219_digits digit)
{
	for(uint8_t reg = REG_DIGIT_0; reg <= REG_DIGIT_7; reg++)
	{
		MAX7219_sendDataWithLatch(digit, reg, 0x00U);
	}
}

/**
 * @brief	This function sets the number of digits to be displayed.
 * @param 	digit - The digit indicates which digit of the matrix driver to transfer data to.
 * 					This parameter can be any value of @ref USH_MAX7219_digits.
 * @param 	scanLimit - The number of digits to be displayed.
 * @retval	None.
 */
void MAX7219_scanLimit(USH_MAX7219_digits digit, USH_MAX7219_REG_SCAN_LIMIT scanLimit)
{
	MAX7219_sendDataWithLatch(digit, REG_SCAN_LIMIT, scanLimit);
}

/**
 * @brief 	TThis function sets the intensity of the glow.
 * @param 	digit - The digit indicates which digit of the matrix driver to transfer data to.
 * 					This parameter can be any value of @ref USH_MAX7219_digits.
 * @param 	intensity - The value of intensity of the glow.
 * 					  This parameter can be any value of @ref USH_MAX7219_REG_INTENSITY.
 * @retval	None.
 */
void MAX7219_intensity(USH_MAX7219_digits digit, USH_MAX7219_REG_INTENSITY intensity)
{
	MAX7219_sendDataWithLatch(digit, REG_INTENSITY, intensity);
}

/**
 * @brief	This function sets the decoding mode for the matrix driver
 * @param	digit - The digit indicates which digit of the matrix driver to transfer data to.
 * 					This parameter can be any value of @ref USH_MAX7219_digits.
 * @param	mode - The decode mode. This parameter can be any value of @ref USH_MAX7219_REG_DECODE_MODE.
 * @retval	None.
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
