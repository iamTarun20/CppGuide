cmake_minimum_required(VERSION 4.3)
project(CPPguide)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPPguide
        Memory_Management/StackAndHeap.cpp)
add_executable(CPPuide Memory_Management/PointerAndReference.cpp)
add_executable(cp Memory_Management/DynamicAllocation.cpp
        Memory_Management/headers/Disk_Management.h
        Memory_Management/headers/cache_manager.h

)
add_executable(raii_demo
        Memory_Management/CppPrerequisite/LanguageMechanics/MemoryManagement/RAII.cpp

)
add_executable(move_demo
        Memory_Management/CppPrerequisite/LanguageMechanics/MemoryManagement/MoveSemantics.cpp
        )
add_executable(chrono
        Memory_Management/CppPrerequisite/LanguageMechanics/MemoryManagement/chrono.cpp

)
add_executable(atomic
        Memory_Management/CppPrerequisite/LanguageMechanics/MemoryManagement/atomic.cpp)