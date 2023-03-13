include_directories(.)

IF(MCU)
   add_subdirectory( manual_tests )
   add_subdirectory( external )
ENDIF()
add_subdirectory( driver )
