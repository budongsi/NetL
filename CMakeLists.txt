cmake_minimum_required(VERSION 3.14)
project(NetL)

SET(CMAKE_C_COMPILER "g++.exe")
SET(CMAKE_C_FLAGS "-g")
SET(CMAKE_CXX_FLAGS "-g")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH lib)

include_directories(NetL)

link_libraries("C:/cygwin64/lib/libgtest.a")


if(CMAKE_C_COMPILER)
	 message("-------------------- CMake is Running --------------------")
endif()

#[[
add_executable(main
	 main.cpp
	 )

add_executable(md_echo_server
	 test/md_echo_server.cpp
	 )

add_executable(md_echo_client
	 test/md_echo_client.cpp
	 )

add_executable(unp_echo_server
	 test/unp_echo_server.cpp
	 )

add_executable(unp_echo_client
	 test/unp_echo_client.cpp
	 )

add_executable(gtest_EventLoopClass
	 NetL/EventLoop.cpp
	 test/gtest_EventLoopClass.cpp
)

add_executable(mtest_EventLoopClass_01
	 NetL/EventLoop.cpp
	 test/mtest_EventLoopClass_01.cpp
)

add_executable(mtest_EventLoopClass_02
	 NetL/EventLoop.cpp
	 test/mtest_EventLoopClass_02.cpp
)
]]

add_executable(mtest_EventLoopClass_03
	 NetL/Poller.cpp
	 NetL/Channel.cpp
	 NetL/EventLoop.cpp
	 test/mtest_EventLoopClass_03.cpp
)





