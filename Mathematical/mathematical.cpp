#include "mathematical.h"

/**
   Sourse:
   https://stackoverflow.com/questions/1838368/calculating-the-amount-of-combinations
 */
ull_t nCr(ull_t n, ull_t r) {
    if (r > n) return 0;
    ull_t res = 1;
    for (ull_t d = 1; d <= r; ++d) {
        res *= n--;
        res /= d;
    }
    return res;
}

ull_t factorial(ull_t n) {
    if (n < 2) return 1;

    ull_t res = 1;
    for (ull_t mult = 2; mult <= n; ++mult) res *= mult;
    return res;
}

std::vector<ull_t> factorialSeries(ull_t n) {
    if (n < 2) return std::vector<ull_t> (n+1,1);

    std::vector<ull_t> res(2, 1);
    res.reserve(n + 1);
    for (int i = 2; i < n + 1; ++i) res.push_back(i * res[i - 1]);
    return res;
}
