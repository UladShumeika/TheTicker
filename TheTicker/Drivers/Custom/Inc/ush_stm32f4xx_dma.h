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

/**
 * @brief DMA memory data size enumeration
 */
typedef enum
{
	DMA_MEMORY_SIZE_BYTE		= 0x00UL,				/* Memory data alignment: Byte */
	DMA_MEMORY_SIZE_HALFWORD	= DMA_SxCR_MSIZE_0,		/* Memory data alignment: Half word */
	DMA_MEMORY_SIZE_WORD		= DMA_SxCR_MSIZE_1		/* Memory data alignment: Word	*/
} USH_DMA_memoryDataSize;

/**
 * @brief DMA mode enumeration
 */
typedef enum
{
	DMA_NORMAL_MODE			= 0x00UL,			/* Normal mode */
	DMA_CIRCULAR_MODE		= DMA_SxCR_CIRC,	/* Circular mode */
	DMA_DOUBLE_BUFFERING	= DMA_SxCR_DBM,  	/* Double buffering mode */
	DMA_PERIPH_CTRL_MODE	= DMA_SxCR_PFCTRL	/* Peripheral control mode */
} USH_DMA_mode;

/**
 * @brief DMA priority enumeration
 */
typedef enum
{
	DMA_PRIORITY_LOW		= 0x0000UL,		/* Priority level: Low */
	DMA_PRIORITY_MEDIUM		= 0x4000UL,		/* Priority level: Medium */
	DMA_PRIORITY_HIGH		= 0x8000UL,		/* Priority level: High */
	DMA_PRIORITY_VERY_HIGH	= 0x30000UL		/* Priority level: Low */
} USH_DMA_priority;

/**
 * @brief DMA memory burst enumeration
 */
typedef enum
{
	DMA_MBURST_SINGLE	= 0x0000000UL,	/* Single transfer configuration */
	DMA_MBURST_INCR4	= 0x0800000UL,	/* Incremental burst of 4 beats */
	DMA_MBURST_INCR8	= 0x1000000UL,	/* Incremental burst of 8 beats */
	DMA_MBURST_INCR16	= 0x1800000UL	/* Incremental burst of 16 beats */
} USH_DMA_memoryBurst;

/**
 * @brief DMA peripheral burst enumeration
 */
typedef enum
{
	DMA_PBURST_SINGLE	= 0x000000UL,	/* Single transfer configuration */
	DMA_PBURST_INCR4	= 0x200000UL,	/* Incremental burst of 4 beats */
	DMA_PBURST_INCR8	= 0x400000UL,	/* Incremental burst of 8 beats */
	DMA_PBURST_INCR16	= 0x600000UL	/* Incremental burst of 16 beats */
} USH_DMA_periphBurst;

/**
 * @brief DMA FIFO mode enumeration
 */
typedef enum
{
	DMA_FIFO_MODE_ENABLE	= 0x04U,	/* FIFO mode enable */
	DMA_FIFO_MODE_DISABLE	= 0x00U		/* FIFO mode disable */
} USH_DMA_fifoMode;

/**
 * @brief DMA FIFO threshold level enumeration
 */
typedef enum
{
	DMA_FIFO_THRESHOLD_1QUARTER		= 0x00U,	/* FIFO threshold 1 quart full configuration */
	DMA_FIFO_THRESHOLD_HALF			= 0x01U,	/* FIFO threshold half full configuration */
	DMA_FIFO_THRESHOLD_3QUARTER		= 0x02U,	/* FIFO threshold 3 quart full configuration */
	DMA_FIFO_THRESHOLD_FULL			= 0x03U		/* FIFO threshold full configuration */
} USH_DMA_fifoThresholdLevel;

#endif /* __USH_STM32F4XX_DMA_H */
