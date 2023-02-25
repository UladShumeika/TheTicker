/**
  ******************************************************************************
  * @file    ush_dma.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    05-February-2023
  * @brief   DMA module driver
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_dma.h"
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static uint32_t DMA_calcBaseAndIndex(USH_DMA_initTypeDef *initStructure);

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
	DMA_TypeDef *reg;

	DMA_state(initStructure->Stream, DISABLE);

	// Get the CR register value
	tmpReg = initStructure->Stream->CR;

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
	initStructure->Stream->CR = tmpReg;

	// Get the FCR register value
	tmpReg = initStructure->Stream->FCR;

	// Clear direct mode and FIFO threshold bits
	tmpReg &= ~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

	// Prepare the DMA stream FIFO configuration
	tmpReg |= initStructure->FIFOMode;

	if(initStructure->FIFOMode == DMA_FIFO_MODE_ENABLE)
	{
		tmpReg |= initStructure->FIFOThreshold;
	}

	// Write to DMA stream FCR
	initStructure->Stream->FCR = tmpReg;

	// Calculate DMA base adress and DMA stream index
	reg = (DMA_TypeDef*)DMA_calcBaseAndIndex(initStructure);

	// Clear all interrupt flags
	if(initStructure->StreamIndex < 4U)
	{
		// add clearing code
	}
}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function enables and disables the selected DMA stream.
 * @param 	DMAx_Streamy - A pointer to a DMA_Stream_TypeDef structure that contains the selected DMA stream.
 * @param 	state - The state of the selected stream. This parameter can be a value of @ref FunctionalState.
 * @retval	None.
 */
void DMA_state(DMA_Stream_TypeDef *DMAx_Streamy, FunctionalState state)
{
	if(state == ENABLE)
	{
		DMAx_Streamy->CR |= DMA_SxCR_EN;
	} else
	{
		DMAx_Streamy->CR &= ~DMA_SxCR_EN;
	}
}

/**
 * @brief 	This function returns the DMA stream base address depending on stream number.
 * @param 	initStructure - A pointer to a USH_DMA_initTypeDef structure that contains the configuration
 * 							information for the specified DMA peripheral.
 * @return	Stream base address.
 */
static uint32_t DMA_calcBaseAndIndex(USH_DMA_initTypeDef *initStructure)
{
	uint32_t streamNumber = (((uint32_t)initStructure->Stream & 0xFFU) - 16U) / 24U;

	// lookup table for necessary stream index of flags within status registers
	static const uint8_t flagBitshiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
	initStructure->StreamIndex = flagBitshiftOffset[streamNumber];

	if (streamNumber > 3U)
	{
		// return pointer to HISR and HIFCR
		initStructure->StreamBaseAddress = (((uint32_t)initStructure->Stream & (uint32_t)(~0x3FFU)) + 4U);
	} else
	{
	    // return pointer to LISR and LIFCR
		initStructure->StreamBaseAddress = ((uint32_t)initStructure->Stream & (uint32_t)(~0x3FFU));
	}

	return initStructure->StreamBaseAddress;
}
