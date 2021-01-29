link_libraries(${LIBS})

add_executable(mt_EventLoopClass_01 mt_EventLoopClass_01.cpp)
target_link_libraries(mt_EventLoopClass_01 NetLnet NetLbase)

add_executable(mt_EventLoopClass_02 mt_EventLoopClass_02.cpp)
target_link_libraries(mt_EventLoopClass_02 NetLnet NetLbase)

add_executable(mt_EventLoopClass_03 mt_EventLoopClass_02.cpp)
target_link_libraries(mt_EventLoopClass_03 NetLnet NetLbase)

add_executable(mt_EventLoop+PollPoller+Channel mt_EventLoop+PollPoller+Channel.cpp)
target_link_libraries(mt_EventLoop+PollPoller+Channel NetLnet NetLbase)

add_executable(mt_EventLoop+PollPoller+Channel_01 mt_EventLoop+PollPoller+Channel_01.cpp)
target_link_libraries(mt_EventLoop+PollPoller+Channel_01 NetLnet NetLbase)