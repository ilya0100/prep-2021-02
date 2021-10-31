#include "matrix.h"

#define ROWS 2
#define COLS 2


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
    Matrix* matrix1 = inv(matrix);
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            get_elem(matrix1, i, j, &buffer);
            printf("%lf ", buffer);
        }
        printf("\n");
    }
    printf("\n");
    printf("%zu %zu\n", matrix->rows_count, matrix->cols_count);
    printf("%zu %zu\n", matrix1->rows_count, matrix1->cols_count);
    free_matrix(matrix);
    free_matrix(matrix1);
    return 0;
}

