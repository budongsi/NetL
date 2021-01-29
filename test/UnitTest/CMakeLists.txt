link_libraries(${LIBS})

add_executable(ut_EventLoopClass ut_EventLoopClass.cpp)
target_link_libraries(ut_EventLoopClass NetLnet NetLbase)