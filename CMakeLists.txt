cmake_minimum_required(VERSION 4.3)
project(CPPguide)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPPguide
        Memory_Management/StackAndHeap.cpp)
add_executable(CPPuide Memory_Management/PointerAndReference.cpp)
add_executable(cp Memory_Management/DynamicAllocation.cpp
        Memory_Management/headers/Disk_Management.h
        Memory_Management/headers/cache_manager.h
        Memory_Management/cache_manager.cpp)
