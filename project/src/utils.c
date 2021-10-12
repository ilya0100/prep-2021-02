#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from ; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        i ? printf(" ") : printf("\n");
    }
    return counter;
}

// TODO(ilya): Implement `power of` function

int custom_pow(int base, int power) {
    if (base == 0) {
        return 0;
    }
    if (base == 1 || power == 0) {
        return 1;
    }
    int res = base;
    for (int i = 2; i <= power; ++i) {
        res *= base;
    }
    return res;
}
