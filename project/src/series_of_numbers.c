#include "series_of_numbers.h"

void print_series_of_numbers(const int number) {
    if (number > 1) {
        print_series_of_numbers(number - 1);
        printf(" ");
    }
    if (number < 1) {
        print_series_of_numbers(number + 1);
        printf(" ");
    }
    printf("%d", number);
    return;
}
