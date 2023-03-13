add_subdirectory( openamp )

# The default HAL configuration. If you need some HAL component is any part of
# the project, uncomment the appropriate line
add_library(mcu_hal stm32mp1xx_hal_conf.h)
target_link_libraries(mcu_hal
   HAL::STM32::MP1
   CMSIS::STM32::MP157AX # for a custom linker script
   ${CMSIS_MP1_MP157AX_STARTUP}
#   CMSIS::STM32::MP157AA # for the default linker script
   HAL::STM32::MP1::CORTEX
   HAL::STM32::MP1::RCC
   HAL::STM32::MP1::RCCEx
   HAL::STM32::MP1::GPIO
   HAL::STM32::MP1::USART
   HAL::STM32::MP1::USARTEx
   HAL::STM32::MP1::UART
   HAL::STM32::MP1::UARTEx
   HAL::STM32::MP1::DMA
   HAL::STM32::MP1::SPI
   HAL::STM32::MP1::PWR
   HAL::STM32::MP1::HSEM
   HAL::STM32::MP1::EXTI
   HAL::STM32::MP1::TIM
   HAL::STM32::MP1::TIMEx
   HAL::STM32::MP1::I2C
   HAL::STM32::MP1::I2CEx
)
stm32_add_linker_script(mcu_hal INTERFACE stm32mp15xx_m4.ld)
target_include_directories(mcu_hal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# We replace the default syscalls to the epmty ones to reduce the firmware size
# written in C++.
set(EMPTY_SYSCALLS
   stm32fx_sys.c
   error_handling.c
   error_handling_pp.cpp
)
add_library(mcu_libc INTERFACE IMPORTED GLOBAL)
target_sources(mcu_libc INTERFACE ${EMPTY_SYSCALLS})
target_link_libraries(mcu_libc INTERFACE
   mcu_hal
   STM32::Nano
)
