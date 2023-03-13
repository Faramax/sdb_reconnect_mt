# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
# this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# this is just for reference
SET(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_SDK_PATH "/opt/st/skrm/3.1-snapshot")

# Without storing SDK path inside environment, C compiler check fails
if(DEFINED ENV{SKRM_SDK_PATH})
    if (NOT CMAKE_SDK_PATH)  # CMake variable is not set, use environment one
        set(CMAKE_SDK_PATH $ENV{SKRM_SDK_PATH})
    endif()
    message("CMAKE_SDK_PATH=${CMAKE_SDK_PATH}")
else()
    if (CMAKE_SDK_PATH)  # Environment variable is not set, use CMake one
        set(ENV{SKRM_SDK_PATH} ${CMAKE_SDK_PATH})
        message("CMAKE_SDK_PATH=${CMAKE_SDK_PATH}")
    else()
        # Neither environment nor CMake variable is set.
        message(FATAL_ERROR "Set up CMAKE_SDK_PATH before running")
    endif()
endif()

SET(SYSROOT_PATH ${CMAKE_SDK_PATH}/sysroots/cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi)
SET(CROSS_PREFIX ${CMAKE_SDK_PATH}/sysroots/x86_64-ostl_sdk-linux/usr/bin/arm-ostl-linux-gnueabi/arm-ostl-linux-gnueabi-)
SET(OE_QMAKE_PATH_EXTERNAL_HOST_BINS ${CMAKE_SDK_PATH}/sysroots/x86_64-ostl_sdk-linux/usr/bin)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${CROSS_PREFIX}gcc)
SET(CMAKE_CXX_COMPILER ${CROSS_PREFIX}g++)

SET(ARCH_FLAGS "-mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7")
SET(CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} ${ARCH_FLAGS}")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ARCH_FLAGS}")

# where is the target environment
SET(CMAKE_SYSROOT ${SYSROOT_PATH})
SET(CMAKE_FIND_ROOT_PATH ${SYSROOT_PATH})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

