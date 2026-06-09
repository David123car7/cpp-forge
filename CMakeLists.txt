cmake_minimum_required(VERSION 3.10)
project(cpp-forge)
set(CMAKE_CXX_STANDARD_20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

add_executable(cpp-forge src/Main.cpp)
target_include_directories(cpp-forge PRIVATE include) 



