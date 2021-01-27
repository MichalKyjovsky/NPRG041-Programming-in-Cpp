cmake_minimum_required(VERSION 3.17)

project(Lecture_06)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lecture_06 double_wrapper.hpp duck_type_array.cpp duck_type_array.hpp int_wrapper.hpp string_wrapper.hpp main.cpp)
