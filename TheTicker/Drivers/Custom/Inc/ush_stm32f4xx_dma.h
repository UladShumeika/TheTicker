/**
  ******************************************************************************
  * @file    ush_stm32f4xx_dma.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    04-February-2023
  * @brief   Header file of DMA module
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_DMA_H
#define __USH_STM32F4XX_DMA_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
 * @brief DMA channels enumeration to select the channel for DMA
 */
typedef enum
{
	DMA_CHANNEL_0	= 0x00000000U,		/* DMA Channel 0 */
	DMA_CHANNEL_1	= 0x02000000U,		/* DMA Channel 1 */
	DMA_CHANNEL_2	= 0x04000000U,		/* DMA Channel 2 */
	DMA_CHANNEL_3	= 0x06000000U,		/* DMA Channel 3 */
	DMA_CHANNEL_4 	= 0x08000000U,		/* DMA Channel 4 */
	DMA_CHANNEL_5	= 0x0A000000U,		/* DMA Channel 5 */
	DMA_CHANNEL_6	= 0x0C000000U,		/* DMA Channel 6 */
	DMA_CHANNEL_7	= 0x0E000000U		/* DMA Channel 7 */
} USH_DMA_channels;

/**
 * @brief DMA data transfer direction enumeration
 */
typedef enum
{
	DMA_PERIPH_TO_MEMORY	= 0x00UL,			/* Peripheral to memory direction */
	DMA_MEMORY_TO_PERIPH	= DMA_SxCR_DIR_0,	/* Memory to peripheral direction */
	DMA_MEMORY_TO_MEMORY	= DMA_SxCR_DIR_1	/* Memory to memory direction */
} USH_DMA_dataTransferDirection;

/**
 * @brief DMA peripheral incremented mode enumeration
 */
typedef enum
{
	DMA_PINC_ENABLE		= DMA_SxCR_PINC,	/* Peripheral increment mode enable */
	DMA_PINC_DISABLE	= 0x00UL			/* Peripheral increment mode disable */
} USH_DMA_periphIncrement;

/**
 * @brief DMA memory incremented mode enumeration
 */
typedef enum
{
	DMA_MINC_ENABLE		= DMA_SxCR_MINC,	/* Memory increment mode enable */
	DMA_MINC_DISABLE	= 0x00UL			/* Memory increment mode disable */
} USH_DMA_memoryIncrement;

/**
 * @brief DMA peripheral data size enumeration
 */
typedef enum
{
	DMA_PERIPH_SIZE_BYTE		= 0x000UL,  			/* Peripheral data alignment: Byte */
	DMA_PERIPH_SIZE_HALFWORD	= DMA_SxCR_PSIZE_0,		/* Peripheral data alignment: Half word	*/
	DMA_PERIPH_SIZE_WORD		= DMA_SxCR_PSIZE_1		/* Peripheral data alignment: Word */
} USH_DMA_periphDataSize;

#endif /* __USH_STM32F4XX_DMA_H */
