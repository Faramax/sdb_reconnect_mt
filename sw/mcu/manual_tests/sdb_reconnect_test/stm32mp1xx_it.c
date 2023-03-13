/**
  ******************************************************************************
  * @file    stm32mp1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include <stm32mp1xx_hal.h>
#include <mcu/external/openamp/ipcc.h>
#include <mcu/driver/general/error_handler.h>
#include "stm32mp1xx_hal_rcc.h"

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
   Error_Handler();
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* STM32MP1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32mp1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles IPCC RX1 occupied interrupt.
  */
void IPCC_RX1_IRQHandler(void)
{
  HAL_IPCC_RX_IRQHandler(&hipcc);
}

/**
  * @brief This function handles IPCC TX1 free interrupt.
  */
void IPCC_TX1_IRQHandler(void)
{
  HAL_IPCC_TX_IRQHandler(&hipcc);
}

/**
  * @brief This function handles RCC wake-up interrupt.
  */
void RCC_WAKEUP_IRQHandler(void)
{
  HAL_RCC_WAKEUP_IRQHandler();
}
