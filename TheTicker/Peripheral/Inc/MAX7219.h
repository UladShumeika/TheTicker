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
