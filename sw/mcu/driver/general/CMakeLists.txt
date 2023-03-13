IF(MCU)
   set(SOURCES
#      delay.h
#      delay.c
#      pin.h
#      pin.cpp
#      callback_registrar.hpp
#      stgenr.h
#      stgenr.c
#      lock_resource.h
#      lock_resource.c
      error_handler.h
      error_handler.c
#      clock.h
#      clock.c
#      chatter_filter_32bit.hpp
#      chatter_filter_32bit.cpp
   )
   source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
   add_library(mcu_driver ${SOURCES})
   target_link_libraries(mcu_driver
      mcu_hal
      mcu_exchange_algo
   )
ENDIF()
#IF(X86)
#   set(SOURCES
#      chatter_filter_autotest.cpp
#      chatter_filter_32bit.hpp
#      chatter_filter_32bit.cpp)
#   source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
#   add_executable(autotest_mcu_driver ${SOURCES})
#   find_package(Boost COMPONENTS system unit_test_framework REQUIRED)
#   target_link_libraries(autotest_mcu_driver ${Boost_LIBRARIES})
#   add_jenkins_test(autotest_mcu_driver)
#ENDIF()
