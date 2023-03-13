# Logic library
add_library(mcu_exchange_algo
#   sdb_status.hpp
   bcm_parser.cpp
   bcm_parser.hpp
   buffer_ctrl.hpp
   buffer_ctrl.cpp
#   tickets_checker.hpp
#   tickets_checker.cpp
)

## Autotest
#IF(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM")
#   find_package(Boost COMPONENTS system unit_test_framework REQUIRED)
#   add_executable(autotest_mcu_exchange
#      buffer_ctrl_autotest.cpp)
#   target_link_libraries(autotest_mcu_exchange
#      mcu_exchange_algo
#      ${Boost_LIBRARIES})
#   add_jenkins_test(autotest_mcu_exchange)
#ENDIF()

## Firmware library
#IF(MCU)
#   add_library(mcu_exchange
#      sdb.hpp
#      sdb.cpp
#      m5_proto_mcu.cpp
#      m5_proto_mcu.hpp
#   )
#   target_link_libraries(mcu_exchange
#      mcu_hal
#      cpp_amp
#      proto
#      mcu_exchange_algo
#   )
#   target_compile_options(mcu_exchange PRIVATE -Wno-unused-parameter -Wno-empty-body -Wno-error)
#ENDIF()
