#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

// Vector printer
template <typename T>
void printVec(std::vector<T>& v);
template <typename T>
void printVec(std::vector<T>&& v);
template <typename T>
void printVec2(std::vector<std::vector<T>>& vv);
template <typename T>
void printVec2(std::vector<std::vector<T>>&& vv);
#include "printer.cc"  // Template implementations should be included here.

#endif  // PRINTER_H
