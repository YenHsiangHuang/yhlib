/**
   For template implementations, I have to include all libraries needed in .cc
   file, not just in .h file.
 */
#include <iostream>
#include <vector>

template <typename T>
void printVec(std::vector<T>& v) {
    std::cout << "[";
    if (v.empty()) std::cout << " ";
    for (auto& elem : v) std::cout << elem << " ";
    std::cout << "\b]\n";
}
template <typename T>
void printVec(std::vector<T>&& v) {
    printVec(v);
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
