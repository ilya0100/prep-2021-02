#include "matrix.h"

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* path_file_fd = fopen(path_file, "r");
    if (path_file_fd == NULL) {
        perror("error");
        return NULL;
    }
    size_t rows = 0, cols = 0;
    if (fscanf(path_file_fd, "%zu %zu", &rows, &cols) == -1) {
        perror("error");
        fclose(path_file_fd);
        return NULL;
    }
    Matrix* matrix_from_file = create_matrix(rows, cols);
    for (size_t i = 0; i < rows * cols; ++i) {
        fscanf(path_file_fd, "%lf", &matrix_from_file->elements[i]);
    }
    fclose(path_file_fd);
    return matrix_from_file;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* new_matrix = malloc(sizeof(Matrix));
    if (new_matrix == NULL) {
        perror("error");
        return NULL;
    }
    new_matrix->rows_count = rows;
    new_matrix->cols_count = cols;
    new_matrix->elements = malloc(sizeof(double)*rows*cols);
    if (new_matrix->elements == NULL) {
        perror("error");
        free(new_matrix);
        return NULL;
    }
    return new_matrix;
}

void free_matrix(Matrix* matrix) {
    free(matrix->elements);
    free(matrix);
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL) {
        return -1;
    }
    *rows = matrix->rows_count;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL) {
        return -1;
    }
    *cols = matrix->cols_count;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL) {
        return -1;
    }
    *val = matrix->elements[(row - 1) * matrix->cols_count + (col - 1)];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return -1;
    }
    matrix->elements[(row - 1) * matrix->cols_count + (col - 1)] = val;
    return 0;
}
