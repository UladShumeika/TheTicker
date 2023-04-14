/**
  ******************************************************************************
  * @file    ush_stm32f4xx_dma.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    04-February-2023
  * @brief	 This file contains the implementation of functions for working with DMA.
  *
  *	NOTE: This file is not a full-fledged DMA driver, but contains only some of
  * 	  the functions that are needed for the current project.
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_stm32f4xx_dma.h"

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes the DMAx peripheral according to the specified parameters in the USH_DMA_initTypeDef.
 * @param 	initStructure - A pointer to a USH_DMA_initTypeDef structure that contains the configuration
 * 							information for the specified DMA peripheral.
 * @retval	None.
 */
void DMA_init(USH_DMA_initTypeDef *initStructure)
{
	uint32_t tmpReg = 0;

	// check parameters
	assert_param(IS_DMA_STREAM_ALL_INSTANCE(initStructure->DMAy_Streamx));
	assert_param(IS_DMA_CHANNEL(initStructure->Channel));
	assert_param(IS_DMA_DIRECTION(initStructure->Direction));
	assert_param(IS_DMA_PERIPH_INC(initStructure->PeriphInc));
	assert_param(IS_DMA_MEM_INC(initStructure->MemInc));
	assert_param(IS_DMA_PERIPH_SIZE(initStructure->PeriphDataAlignment));
	assert_param(IS_DMA_MEM_SIZE(initStructure->MemDataAlignment));
	assert_param(IS_DMA_MODE(initStructure->Mode));
	assert_param(IS_DMA_PRIORITY(initStructure->Priority));
	assert_param(IS_DMA_MBURST(initStructure->MemBurst));
	assert_param(IS_DMA_PBURST(initStructure->PeriphBurst));
	assert_param(IS_DMA_FIFO_MODE(initStructure->FIFOMode));
	assert_param(IS_DMA_FIFO_THRESHOLD(initStructure->FIFOThreshold));

	DMA_state(initStructure->DMAy_Streamx, DISABLE);

	// Get the CR register value
	tmpReg = initStructure->DMAy_Streamx->CR;

	// Clear all bits except PFCTRL, TCIE, HTIE, TEIE, DMEIE, EN
	tmpReg &= 0x3FU;

	// Prepare the DMA Stream configuration
	tmpReg |= initStructure->Channel   | initStructure->MemDataAlignment 	| initStructure->MemInc	   |
			  initStructure->Direction | initStructure->PeriphDataAlignment	| initStructure->PeriphInc |
			  initStructure->Mode 	   | initStructure->Priority;

	// The memory burst and peripheral burst are not used when the FIFO is disabled
	if(initStructure->FIFOMode == DMA_FIFO_MODE_ENABLE)
	{
		tmpReg |= initStructure->MemBurst | initStructure->PeriphBurst;
	}

	// Write to DMA Stream CR register
	initStructure->DMAy_Streamx->CR = tmpReg;

	// Get the FCR register value
	tmpReg = initStructure->DMAy_Streamx->FCR;

	// Clear direct mode and FIFO threshold bits
	tmpReg &= ~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

	// Prepare the DMA stream FIFO configuration
	tmpReg |= initStructure->FIFOMode;

	if(initStructure->FIFOMode == DMA_FIFO_MODE_ENABLE)
	{
		tmpReg |= initStructure->FIFOThreshold;
	}

	// Write to DMA stream FCR
	initStructure->DMAy_Streamx->FCR = tmpReg;

	// Clear stream interrupt flags
	DMA_clearFlags(initStructure->DMAy_Streamx, DMA_FLAG_ALL);
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function enables and disables the selected DMA stream.
 * @param 	DMAy_Streamx - A pointer to Stream peripheral to be used where y is 1 or 2 and x is from 0 to 7.
 * @param 	state - The state of the selected stream. This parameter can be a value of @ref FunctionalState.
 * @retval	None.
 */
void DMA_state(DMA_Stream_TypeDef *DMAy_Streamx, FunctionalState state)
{
	// Check parameters
	assert_param(IS_DMA_STREAM_ALL_INSTANCE(DMAy_Streamx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	if(state == ENABLE)
	{
		DMAy_Streamx->CR |= DMA_SxCR_EN;
	} else
	{
		DMAy_Streamx->CR &= ~DMA_SxCR_EN;
	}
}
