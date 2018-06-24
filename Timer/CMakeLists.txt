cmake_minimum_required(VERSION 3.1)

file(GLOB files *.cc *.h)
add_library(timer STATIC ${files})
target_include_directories(timer PUBLIC .)
