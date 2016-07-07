cmake_minimum_required(VERSION 3.3)
project(clion_work_space)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp OIBigInt.cpp OIBigInt.h)
add_executable(clion_work_space ${SOURCE_FILES})