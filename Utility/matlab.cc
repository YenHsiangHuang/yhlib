#include "matlab.h"
#include <random>

namespace {
std::random_device seed;
// Standard mersenne_twister_engine seeded with seed()
std::mt19937 gen(seed());
}  // namespace

std::vector<int> randi(int ub, size_t len) {
    return randi(1, ub, len);
}

std::vector<int> randi(int lb, int ub, size_t len) {
    std::vector<int> res(len);
    std::uniform_int_distribution<> uniform_int_dist(lb, ub);
    for (auto& n : res) n = uniform_int_dist(gen);
    return res;
}
