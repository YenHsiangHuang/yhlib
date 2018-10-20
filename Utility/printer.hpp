#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

// Vector printer
template <typename T>
void printVec(std::vector<T>& v, char eol = '\n') {
    std::cout << "[";
    if (v.empty()) std::cout << " ";
    for (auto& elem : v) std::cout << elem << " ";
    std::cout << "\b]" << eol;
}
template <typename T>
void printVec(std::vector<T>&& v, char eol = '\n') {
    printVec(v, eol);
}

template <typename T>
void printVec2(std::vector<std::vector<T>>& vv) {
    std::cout << "[\n";
    for (auto& v : vv) {
        std::cout.width(4);
        std::cout << "";
        printVec(v);
    }
    std::cout << "]\n";
}
template <typename T>
void printVec2(std::vector<std::vector<T>>&& vv) {
    printVec2(vv);
}

#endif  // PRINTER_H
