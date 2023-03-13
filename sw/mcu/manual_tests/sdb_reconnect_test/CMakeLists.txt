set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wno-error")

# Based on logicanalyser from https://github.com/STMicroelectronics
set(SOURCES
   sdb_reconnect_test.cpp
   stm32mp1xx_it.c
   continious_sender.cpp
   continious_sender.h
   send_data.cpp
   send_data.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(mt_sdb_reconnect ${SOURCES})

target_link_libraries(mt_sdb_reconnect
   mcu_libc
   mcu_hal
   cpp_amp
   mcu_driver
)
