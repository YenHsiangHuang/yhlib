#include "mathematical.h"

/**
   Sourse:
   https://stackoverflow.com/questions/1838368/calculating-the-amount-of-combinations
 */
unsigned long long nCr(unsigned long long n, unsigned long long r) {
    if (r > n) return 0;
    unsigned long long res = 1;
    for (unsigned long long d = 1; d <= r; ++d) {
        res *= n--;
        res /= d;
    }
    return res;
}
