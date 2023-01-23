//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __MAX7219_H
#define __MAX7219_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_spi.h"
//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

/* --------------------- General parameters of the matrix -----------------*/
#define MATRIX_NUM									((uint8_t)4)
#define DELAY_TEST_MODE								((uint16_t)500)

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
 * @brief MAX7219 digits enumeration
 */
typedef enum
{
	FIRST_DIGIT		= 4,
	SECOND_DIGIT    = 3,
	THIRD_DIGIT		= 2,
	FORTH_DIGIT		= 1,
	ALL_DIGITS		= 0xFF
} USH_MAX7219_digits;

/**
 * @brief MAX7219 registers enumeration.
 */
typedef enum
{
	REG_NO_OP = 0,
	REG_DIGIT_0,
	REG_DIGIT_1,
	REG_DIGIT_2,
	REG_DIGIT_3,
	REG_DIGIT_4,
	REG_DIGIT_5,
	REG_DIGIT_6,
	REG_DIGIT_7,
	REG_DECODE_MODE,
	REG_INTENSITY,
	REG_SCAN_LIMIT,
	REG_SHUTDOWN,
	REG_DISPLAY_TEST
} USH_MAX7219_registers;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

/**
  * @brief  This function sends data WITHOUT a latch.
  * @param	digit - The digit indicates which digit of the matrix to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  addr - The matrix controller's address where you want to send data.
  * @param	data - Data to be sent to the matrix controller.
  * @retval None.
  */
void MAX7219_sendDataWithoutLatch(uint8_t digit, uint8_t addr, uint8_t data);

/**
  * @brief  This function sends data WITH a latch.
  * @param  digit - The digit indicates which digit of the matrix to transfer data to.
  * 		        This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  addr - The matrix controller's address where you want to send data.
  * @param	data - Data to be sent to the matrix controller.
  * @retval None.
  */
void MAX7219_sendDataWithLatch(uint8_t digit, uint8_t addr, uint8_t data);

void MAX7219_init(void);

#endif /* __MAX7219_H */
