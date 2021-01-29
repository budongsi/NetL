cmake_minimum_required(VERSION 3.14)
project(NetL)

SET(CMAKE_C_COMPILER "g++.exe")
SET(CMAKE_CXX_FLAGS "-g")
set(LIBS "libgtest.a")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(./ NetL Base)
add_subdirectory(NetL) 
add_subdirectory(Base)
add_subdirectory(test/UnitTest)
add_subdirectory(test/ManualTest)
add_subdirectory(test/OtherTest)

link_libraries(${LIBS})

if(CMAKE_C_COMPILER)
    message("-------------------- CMake is Running --------------------")
endif()

add_executable(main main.cpp)
