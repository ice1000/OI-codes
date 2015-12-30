cmake_minimum_required(VERSION 3.3)
project(clion_work_space)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp save_0x01.cpp copy_1.cpp save_0x02.cpp)
add_executable(clion_work_space ${SOURCE_FILES})