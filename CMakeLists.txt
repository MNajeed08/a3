cmake_minimum_required(VERSION 3.31)
project(MemorySimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(MemorySimulator main.cpp
        simulation.h
        simulation.cpp
        memory_manager.h
        memory_manager.cpp
        firstfit.h
        firstfit.cpp
        bestfit.h
        bestfit.cpp
        memory_request.h
        memory_request.cpp)
