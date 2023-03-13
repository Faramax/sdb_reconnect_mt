find_package(Boost COMPONENTS system program_options REQUIRED)
add_executable(sdb_reconnect_manual_test
   sdb_reconnect_main.cpp
)
target_link_libraries (sdb_reconnect_manual_test
   rpmsg
   ${Boost_LIBRARIES}
)
