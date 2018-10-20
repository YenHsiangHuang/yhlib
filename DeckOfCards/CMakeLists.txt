cmake_minimum_required(VERSION 3.1)

file(GLOB files *.cpp *.hpp)
add_library(deckofcards STATIC ${files})
target_include_directories(deckofcards PUBLIC .)
