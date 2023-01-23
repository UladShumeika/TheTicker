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
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
  * @brief  This function enables or disables a matrix controller.
  * @param  digit - The digit indicates which digit of the matrix to transfer data to.
  * 				This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  mode - The driver mode. This parameter can be any value of @ref USH_MAX7219_REG_SHUTDOWN.
  * @retval None.
  */
void MAX7219_state(uint8_t digit, USH_MAX7219_REG_SHUTDOWN mode)
{
	if(mode == NORMAL_MODE)
	{
		MAX7219_sendDataWithLatch(digit, REG_SHUTDOWN, NORMAL_MODE);
	} else
	{
		MAX7219_sendDataWithLatch(digit, REG_SHUTDOWN, SHUTDOWN_MODE);
	}
}

/**
  * @brief  This function sends data WITHOUT a latch.
  * @param	digit - The digit indicates which digit of the matrix to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  addr - The matrix controller's address where you want to send data.
  * @param	data - Data to be sent to the matrix controller.
  * @retval None.
  */
void MAX7219_sendDataWithoutLatch(uint8_t digit, uint8_t addr, uint8_t data)
{
	uint16_t NoOp = 0;

	for(uint8_t i = 1; i <= MATRIX_NUM; i++)
	{
		if(digit == ALL_DIGITS)
		{
			SPI_writeData(SPI1, addr, data);
		} else
		{
			if(i == digit)
			{
				SPI_writeData(SPI1, addr, data);
			} else
			{
				SPI_writeData(SPI1, NoOp, NoOp);
			}
		}
	}
}

/**
  * @brief  This function sends data WITH a latch.
  * @param  digit - The digit indicates which digit of the matrix to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  addr - The matrix controller's address where you want to send data.
  * @param	data - Data to be sent to the matrix controller.
  * @retval None.
  */
void MAX7219_sendDataWithLatch(uint8_t digit, uint8_t addr, uint8_t data)
{
	SPI_csPin(LOW);
	MAX7219_sendDataWithoutLatch(digit, addr, data);
	SPI_csPin(HIGH);
}
