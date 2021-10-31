#include "matrix.h"


int main(void) {
    Matrix* matrix = create_matrix_from_file("test_file.txt");
    printf("%s", "input matrix:\n");
    double buffer = 0;
    for (size_t i = 0; i < matrix->rows_count; ++i) {
        for (size_t j = 0; j < matrix->cols_count; ++j) {
            get_elem(matrix, i, j, &buffer);
            printf("%lf ", buffer);
        }
        printf("\n");
    }
    printf("\n");
    double determ;
    det(matrix, &determ);
    printf("%s", "determinant:\n");
    printf("%lf\n\n", determ);
    // printf("%zu %zu\n", matrix->rows_count, matrix->cols_count);
    Matrix* matrix1 = inv(matrix);
    if (matrix1 == NULL) {
        printf("%s\n", "error");
    } else {
        // Matrix* mul_matrix = mul(matrix, matrix1);
        printf("%s", "output matrix:\n");
        for (size_t i = 0; i < matrix1->rows_count; ++i) {
            for (size_t j = 0; j < matrix1->cols_count; ++j) {
                get_elem(matrix1, i, j, &buffer);
                printf("%lf ", buffer);
            }
            printf("\n");
        }
        printf("\n");
        // printf("%zu %zu\n", matrix1->rows_count, matrix1->cols_count);
        // free_matrix(mul_matrix);
        free_matrix(matrix1);
    }
    free_matrix(matrix);
    return 0;
}

