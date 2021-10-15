#include "series_of_numbers.h"

void series_of_numbers(int number) {
    if (number > 1) {
        series_of_numbers(number - 1);
        printf(" ");
    }
    if (number < 1) {
        series_of_numbers(number + 1);
        printf(" ");
    }
    printf("%d", number);
    return;
}
