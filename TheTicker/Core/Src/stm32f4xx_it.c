//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"
#include "stm32f4xx_it.h"

//---------------------------------------------------------------------------
// External variables
//---------------------------------------------------------------------------
extern USH_DMA_initTypeDef initDMA_txStructure;
extern USH_DMA_initTypeDef initDMA_rxStructure;
extern USH_USART_initTypeDef uart_structure;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
	while(1)
	{

	}
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
	while(1)
	{

	}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
	while(1)
	{

	}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
	while(1)
	{

	}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
	while(1)
	{

	}
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
	DMA_IRQHandler(&initDMA_txStructure);
}

/**
  * @brief This function handles DMA1 stream7 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
	DMA_IRQHandler(&initDMA_rxStructure);
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
	USART_IRQHandler(&uart_structure);
}
