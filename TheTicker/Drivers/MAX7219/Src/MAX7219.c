/**
  ******************************************************************************
  * @file    MAX7219.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    13-February-2023
  * @brief	 This file contains the implementation of functions for working with MAX7219.
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "MAX7219.h"

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief	This function sets the decoding mode for the matrix driver
 * @param	digit - The digit indicates which digit of the matrix driver to transfer data to.
 * 					This parameter can be any value of @ref USH_MAX7219_digits.
 * @param	mode - The decode mode. This parameter can be any value of @ref USH_MAX7219_REG_DECODE_MODE.
 * @retval	None.
 */
void MAX7219_decodeMode(USH_MAX7219_digits numDigit, USH_MAX7219_REG_DECODE_MODE mode)
{
	MAX7219_sendDataWithLatch(numDigit, REG_DECODE_MODE, mode);
}

/**
  * @brief  This function enables or disables a matrix driver.
  * @param  digit - The digit indicates which digit of the matrix driver to transfer data to.
  * 				This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  mode - The driver mode. This parameter can be any value of @ref USH_MAX7219_REG_SHUTDOWN.
  * @retval None.
  */
void MAX7219_state(uint8_t numDigit, USH_MAX7219_REG_SHUTDOWN mode)
{
	MAX7219_sendDataWithLatch(numDigit, REG_SHUTDOWN, mode);
}

/**
  * @brief  This function sends data WITH a latch.
  * @param  digit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithLatch(uint8_t numDigit, USH_MAX7219_registers reg, uint8_t data)
{
	SPI_csPin(MATRIX_CS_PORT, MATRIX_CS_PIN, LOW);
	MAX7219_sendDataWithoutLatch(numDigit, reg, data);
	SPI_csPin(MATRIX_CS_PORT, MATRIX_CS_PIN, HIGH);
}

/**
  * @brief  This function sends data WITHOUT a latch.
  * @param	numDigit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		           This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * 			  This parameter can be any value of @ref USH_MAX7219_registers.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithoutLatch(USH_MAX7219_digits numDigit, USH_MAX7219_registers reg, uint8_t data)
{
	uint8_t digitPos, pos, currentDigit, NoOp = 0;

	for(digitPos = 0; digitPos < MATRIX_DIGITS; digitPos++)
	{
		if(numDigit == ALL_DIGITS)
		{
			SPI_writeData(MATRIX_SPI, reg, data);
		} else
		{
			pos = (uint8_t)0x01 << digitPos;
			currentDigit = numDigit & pos;

			if(currentDigit == pos)
			{
				SPI_writeData(MATRIX_SPI, reg, data);
			} else
			{
				SPI_writeData(MATRIX_SPI, NoOp, NoOp);
			}
		}
	}
}
