#include "utils.h"

int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i < number / 2; ++i) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}
