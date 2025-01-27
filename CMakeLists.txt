cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DataStructures)

add_executable(DataStructures src/main.cpp)
target_include_directories(DataStructures PRIVATE src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
