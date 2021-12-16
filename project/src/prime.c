#include "prime.h"

int is_prime(const int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}
