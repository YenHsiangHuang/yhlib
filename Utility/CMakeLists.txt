cmake_minimum_required(VERSION 3.6)

add_library(printer STATIC printer.h printer.cc)
target_include_directories(printer PUBLIC .)
add_library(matlab STATIC matlab.h matlab.cc)
target_include_directories(matlab PUBLIC .)
