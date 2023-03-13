set(STM32_FLAGS "${STM32_FLAGS} -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard") #-mthumb -mabi=aapcs
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${STM32_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STM32_FLAGS}")

if(NOT STM32_CUBE_PATH)
   message(FATAL_ERROR "There is no STM32_CUBE_PATH specified")
endif()
set(OPEN_AMP_PATH "${STM32_CUBE_PATH}/Middlewares/Third_Party/OpenAMP")

add_library(
   libmetal
   ${OPEN_AMP_PATH}/libmetal/lib/device.c
   ${OPEN_AMP_PATH}/libmetal/lib/init.c
   ${OPEN_AMP_PATH}/libmetal/lib/io.c
   ${OPEN_AMP_PATH}/libmetal/lib/log.c
   ${OPEN_AMP_PATH}/libmetal/lib/shmem.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/condition.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/generic_device.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/generic_init.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/generic_io.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/generic_shmem.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/time.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/irq.c
   ${OPEN_AMP_PATH}/libmetal/lib/system/generic/cortexm/sys.c
)
target_include_directories(
   libmetal PUBLIC
   ${OPEN_AMP_PATH}/libmetal/lib/include
)
target_compile_definitions(libmetal PRIVATE -DMETAL_INTERNAL)
target_compile_definitions(libmetal PRIVATE -DMETAL_MAX_DEVICE_REGIONS=2)
target_compile_options(libmetal PUBLIC "-Wno-error")

add_library(openamp INTERFACE IMPORTED GLOBAL)
target_sources(openamp INTERFACE
   ${OPEN_AMP_PATH}/virtual_driver/virt_uart.c
   ${OPEN_AMP_PATH}/open-amp/lib/remoteproc/remoteproc_virtio.c
   ${OPEN_AMP_PATH}/open-amp/lib/rpmsg/rpmsg.c
   ${OPEN_AMP_PATH}/open-amp/lib/rpmsg/rpmsg_virtio.c
   ${OPEN_AMP_PATH}/open-amp/lib/virtio/virtio.c
   ${OPEN_AMP_PATH}/open-amp/lib/virtio/virtqueue.c
   ${CMAKE_CURRENT_SOURCE_DIR}/openamp.c
   ${CMAKE_CURRENT_SOURCE_DIR}/openamp.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ipcc.c
   ${CMAKE_CURRENT_SOURCE_DIR}/ipcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/openamp_conf.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mbox_ipcc.c
   ${CMAKE_CURRENT_SOURCE_DIR}/mbox_ipcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/rsc_table.h
   ${CMAKE_CURRENT_SOURCE_DIR}/rsc_table.c
   ${CMAKE_CURRENT_SOURCE_DIR}/rpmsg_hdr.h
   ${CMAKE_CURRENT_SOURCE_DIR}/rpmsg_hdr.c
   ${CMAKE_CURRENT_SOURCE_DIR}/rpmsg_hdr_status.h
)
target_include_directories(
   openamp INTERFACE
   ${OPEN_AMP_PATH}/open-amp/lib/include
   ${OPEN_AMP_PATH}/virtual_driver
   ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
   openamp INTERFACE
   libmetal
   HAL::STM32::MP1
   HAL::STM32::MP1::IPCC
)
target_compile_options(openamp INTERFACE -Wno-unused-parameter -Wno-empty-body -Wno-error -Wno-format)
target_compile_definitions(openamp INTERFACE __STDC_NO_ATOMICS__)


add_library(cpp_amp INTERFACE IMPORTED GLOBAL)
target_sources(cpp_amp INTERFACE
   rpmsg.cpp
   rpmsg.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/stm32mp1xx_hal_msp.c
   printf.cpp
   printf.hpp
)
target_link_libraries(cpp_amp INTERFACE
   openamp
   libmetal
   HAL::STM32::MP1::IPCC
)
