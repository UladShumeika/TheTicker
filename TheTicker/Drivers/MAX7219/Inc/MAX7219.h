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

#endif /* __MAX7219_H */
