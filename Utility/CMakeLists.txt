cmake_minimum_required(VERSION 3.1)

add_library(printer STATIC printer.h printer.cc)
target_include_directories(printer PUBLIC .)
