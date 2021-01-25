cmake_minimum_required(VERSION 3.14)
project(NetL)

SET(CMAKE_C_COMPILER "g++.exe")
SET(CMAKE_C_FLAGS
	 "-g"
)
SET(CMAKE_CXX_FLAGS
    "-g"
)

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
SET(LIBRARY_OUTPUT_PATH lib)

if(CMAKE_C_COMPILER)
	 message("-------------------- CMake is Running --------------------")
endif()

add_executable(main
	 main.cpp
	 )



