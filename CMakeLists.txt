cmake_minimum_required(VERSION 4.3)
project(CPPguide)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPPguide
        Memory_Management/StackAndHeap.cpp)
add_executable(CPPuide Memory_Management/PointerAndReference.cpp)
