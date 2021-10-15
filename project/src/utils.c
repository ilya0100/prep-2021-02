#include "utils.h"

size_t timer_from(const int from) {
    size_t counter = 0;
    for (int i = from ; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        i ? printf(" ") : printf("\n");
    }
    return counter;
}

int custom_pow(const int base, const int power) {
    int res = 1;
    for (int i = 0; i < power; ++i) {
        res *= base;
    }
    return res;
}
