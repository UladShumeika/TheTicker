/**
  ******************************************************************************
  * @file    MAX7219.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    13-February-2023
  * @brief   Header file of MAX7219 module.
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __MAX7219_H
#define __MAX7219_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_spi.h"

//---------------------------------------------------------------------------
// General parameters of the matrix
//---------------------------------------------------------------------------
#define MATRIX_DIGITS								((uint8_t)4)
#define MATRIX_HIGH									((uint8_t)8)

#define DELAY_TEST_MODE								((uint16_t)2000)

#define MATRIX_SPI									(SPI1)
#define MATRIX_CS_PORT								(GPIOA)
#define MATRIX_CS_PIN								(GPIO_PIN_4)

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
 * @brief MAX7219 digits enumeration
 */
typedef enum
{
	DIGIT_1		= 0x08,
	DIGIT_2		= 0x04,
	DIGIT_3		= 0x02,
	DIGIT_4		= 0x01,
	DIGIT_5		= 0x80,
	DIGIT_6		= 0x40,
	DIGIT_7		= 0x20,
	DIGIT_8		= 0x10,
	ALL_DIGITS	= 0xFF
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
	REG_DISPLAY_TEST = 0x0F
} USH_MAX7219_registers;

/**
 * @brief MAX7219 decode mode register's description enumeration.
 */
typedef enum
{
	NO_DECODE_FOR_ALL     	= 0x00,		// No decode for digits 7–0
	CODE_B_DECODE_FOR_0		= 0x01,		// Code B decode for digit 0. No decode for digits 7–1
	CODE_B_DECODE_FOR_3_0	= 0x0F,		// Code B decode for digits 3–0. No decode for digits 7–4
	CODE_B_DECODE_FOR_ALL	= 0xFF		// Code B decode for digits 7–0
} USH_MAX7219_REG_DECODE_MODE;

/**
 * @brief MAX7219 intensity register's description enumeration.
 */
typedef enum
{
	INTENSITY_1_32 = 0,		// min value
	INTENSITY_3_32,
	INTENSITY_5_32,
	INTENSITY_7_32,
	INTENSITY_9_32,
	INTENSITY_11_32,
	INTENSITY_13_32,
	INTENSITY_15_32,
	INTENSITY_17_32,
	INTENSITY_19_32,
	INTENSITY_21_32,
	INTENSITY_23_32,
	INTENSITY_25_32,
	INTENSITY_27_32,
	INTENSITY_29_32,
	INTENSITY_31_32			// max value
} USH_MAX7219_REG_INTENSITY;

/**
 * @brief MAX7219 scan limit register's description enumeration.
 */
typedef enum
{
	SCAN_LIMIT_0 = 0,		// display digit 0 only
	SCAN_LIMIT_0_1,			// display digits 0 & 1
	SCAN_LIMIT_0_2,			// display digits 0 & 2
	SCAN_LIMIT_0_3,			// display digits 0 & 3
	SCAN_LIMIT_0_4,			// display digits 0 & 4
	SCAN_LIMIT_0_5,			// display digits 0 & 5
	SCAN_LIMIT_0_6,			// display digits 0 & 6
	SCAN_LIMIT_0_7			// display digits 0 & 7
} USH_MAX7219_REG_SCAN_LIMIT;

/**
 * @brief MAX7219 shutdown register's description enumeration.
 */
typedef enum
{
	SHUTDOWN_MODE = 0,
	NORMAL_MODE
} USH_MAX7219_REG_SHUTDOWN;

/**
 * @brief MAX7219 display test register's description enumeration.
 */
typedef enum
{
	NORMAL_OPERATION = 0,
	DISPLAY_TEST_MODE
} USH_MAX7219_REG_DISPLAY_TEST;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------

/**
  * @brief  This function enables or disables a matrix driver.
  * @param  numDigit - The digit indicates which digit of the matrix driver to transfer data to.
  * 				   This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  mode - The driver mode. This parameter can be any value of @ref USH_MAX7219_REG_SHUTDOWN.
  * @retval None.
  */
void MAX7219_state(USH_MAX7219_digits numDigit, USH_MAX7219_REG_SHUTDOWN mode);

/**
  * @brief  This function sends data WITH a latch.
  * @param  numDigit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		           This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithLatch(USH_MAX7219_digits numDigit, USH_MAX7219_registers reg, uint8_t data);

/**
  * @brief  This function sends data WITHOUT a latch.
  * @param	numDigit - The digit indicates which digit of the matrix driver to transfer data to.
  * 		           This parameter can be any value of @ref USH_MAX7219_digits.
  * @param  reg - The matrix driver's address where the data should be written.
  * 			  This parameter can be any value of @ref USH_MAX7219_registers.
  * @param	data - Data to be sent to the matrix driver.
  * @retval None.
  */
void MAX7219_sendDataWithoutLatch(USH_MAX7219_digits numDigit, USH_MAX7219_registers reg, uint8_t data);

#endif /* __MAX7219_H */
