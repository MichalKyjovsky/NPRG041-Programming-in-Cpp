cmake_minimum_required(VERSION 3.17)
project(Recodex_assignment_01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_executable(Recodex_assignment_01 main.cpp data_aggregator.cpp data_aggregator.hpp)