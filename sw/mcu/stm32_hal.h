/*
 * stm32fxxx_hal.h
 *
 *  Created on: 16 февр. 2016 г.
 *      Author: krtkr
 */

#ifndef INC_STM32FXXX_HAL_H_
#define INC_STM32FXXX_HAL_H_

#if    defined(STM32F1)
  #include <stm32f1xx_hal.h>
#elif  defined(STM32F2)
  #include <stm32f2xx_hal.h>
#elif  defined(STM32F4)
  #include <stm32f4xx_hal.h>
#elif  defined(STM32F7)
  #include <stm32f7xx_hal.h>
#elif  defined(STM32MP1)
   #include <stm32mp1xx_hal.h>
#else
  #error "No supported chip found."
#endif

#if   defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
      defined(STM32F215xx) || defined(STM32F217xx) || defined(STM32F205xx) || defined(STM32F207xx)
  #define USE_FSMC_CONTROLLER
#elif defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
      defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F745xx) || defined(STM32F765xx) ||\
      defined(STM32F746xx) || defined(STM32F767xx) || defined(STM32F777xx) || defined(STM32F769xx) ||\
      defined(STM32F779xx) || defined(STM32MP1)
  #define USE_FMC_CONTROLLER
#else
  #error "Unknown chip."
#endif

#endif /* INC_STM32FXXX_HAL_H_ */
