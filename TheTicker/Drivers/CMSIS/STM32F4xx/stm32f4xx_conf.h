/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_conf.h  
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
//#include "stm32f4xx_adc.h"
//#include "stm32f4xx_crc.h"
//#include "stm32f4xx_dbgmcu.h"
//#include "stm32f4xx_dma.h"
//#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_i2c.h"
//#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_rtc.h"
//#include "stm32f4xx_sdio.h"
//#include "stm32f4xx_spi.h"
//#include "stm32f4xx_syscfg.h"
//#include "stm32f4xx_tim.h"
//#include "stm32f4xx_usart.h"
//#include "stm32f4xx_wwdg.h"
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#if defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
//#include "stm32f4xx_cryp.h"
//#include "stm32f4xx_hash.h"
//#include "stm32f4xx_rng.h"
//#include "stm32f4xx_can.h"
//#include "stm32f4xx_dac.h"
//#include "stm32f4xx_dcmi.h"
//#include "stm32f4xx_dma2d.h"
//#include "stm32f4xx_fmc.h"
//#include "stm32f4xx_ltdc.h"
//#include "stm32f4xx_sai.h"
#endif /* STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F427_437xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_sai.h"
#endif /* STM32F427_437xx */

#if defined(STM32F40_41xxx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_fsmc.h"
#endif /* STM32F40_41xxx */

#if defined(STM32F410xx)
#include "stm32f4xx_rng.h"
#include "stm32f4xx_dac.h"
#endif /* STM32F410xx */

#if defined(STM32F411xE)
#include "stm32f4xx_flash_ramfunc.h"
#endif /* STM32F411xE */

#if defined(STM32F446xx) || defined(STM32F469_479xx)
#include "stm32f4xx_qspi.h"
#endif /* STM32F446xx || STM32F469_479xx */

#if defined(STM32F410xx) || defined(STM32F446xx)
#include "stm32f4xx_fmpi2c.h"
#endif /* STM32F410xx || STM32F446xx */

#if defined(STM32F446xx)
#include "stm32f4xx_spdifrx.h"
#include "stm32f4xx_cec.h"
#endif /* STM32F446xx */

#if defined(STM32F469_479xx)
#include "stm32f4xx_dsi.h"
#endif /* STM32F469_479xx */

#if defined(STM32F410xx)
#include "stm32f4xx_lptim.h"
#endif /* STM32F410xx */

#if defined(STM32F412xG)
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_qspi.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_dfsdm.h"
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_fmpi2c.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_qspi.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_dfsdm.h"
#endif /* STM32F413_423xx */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* If an external clock source is used, then the value of the following define 
   should be set to the value of the external clock source, else, if no external 
   clock is used, keep this define commented */
/*#define I2S_EXTERNAL_CLOCK_VAL   12288000 */ /* Value of the external clock in Hz */

#endif /* __STM32F4xx_CONF_H */
