#include "series_of_numbers.h"

void series_of_num(int number) {
    if (number > 1) {
        series_of_num(number - 1);
        printf(" ");
    }
    if (number < 1) {
        series_of_num(number + 1);
        printf(" ");
    }
    printf("%d", number);
    return;
}
