#include "matrix.h"

#define ROWS 1
#define COLS 1


int main(void) {
    Matrix* matrix = create_matrix(ROWS, COLS);
    double k = 0;
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            set_elem(matrix, i, j, ++k);
        }
    }
    double buffer = 0;
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            get_elem(matrix, i, j, &buffer);
            printf("%lf ", buffer);
        }
        printf("\n");
    }
    printf("\n");
    matrix = inv(matrix);
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            get_elem(matrix, i, j, &buffer);
            printf("%lf ", buffer);
        }
        printf("\n");
    }
    free_matrix(matrix);
    return 0;
}

