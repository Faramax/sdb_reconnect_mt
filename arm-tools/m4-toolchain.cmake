# Unfortunately, the gcc-arm-none-eabi from the sysroot doesn't work. It aborts with an error.
#set(STM32_TOOLCHAIN_PATH /opt/st/myir/3.1-snapshot/sysroots/x86_64-ostl_sdk-linux/usr/share/gcc-arm-none-eabi)

# Using a standalone toolchain instead
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/gcc")
   message(FATAL_ERROR
      "Not found a gcc in the ${CMAKE_CURRENT_LIST_DIR}.\n
      Please extract the toolchain by running the command\n
      \n
      7z x ${CMAKE_CURRENT_LIST_DIR}/gcc-arm-none-eabi/gcc-arm-none-eabi-10-2020-q4-major.7z -aos -o${CMAKE_CURRENT_LIST_DIR}/gcc\n
      Then clear the build directory and run cmake again.")
endif()
set(STM32_TOOLCHAIN_PATH ${CMAKE_CURRENT_LIST_DIR}/gcc)

set(STM32_CUBE_MP1_PATH ${CMAKE_CURRENT_LIST_DIR}/STM32CubeMP1)
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(CMAKE_NO_SYSTEM ON)
include(${CMAKE_CURRENT_LIST_DIR}/stm32-cmake/cmake/stm32_gcc.cmake)
