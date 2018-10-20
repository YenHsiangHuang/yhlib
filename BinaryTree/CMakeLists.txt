cmake_minimum_required(VERSION 3.1)

file(GLOB files *.cpp *.hpp)
add_library(binarytree STATIC ${files})
target_include_directories(binarytree PUBLIC .)
