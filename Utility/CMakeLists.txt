cmake_minimum_required(VERSION 3.1)

add_library(printer STATIC printer.hpp printer.cpp)
target_include_directories(printer PUBLIC .)

add_library(matlab STATIC matlab.hpp matlab.cpp)
target_include_directories(matlab PUBLIC .)
