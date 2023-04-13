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

#endif /* __MAX7219_H */
