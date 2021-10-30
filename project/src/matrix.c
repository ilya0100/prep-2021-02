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
    new_matrix->elements = malloc(sizeof(double) * rows * cols);
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
    if (row + 1 > matrix->rows_count || col + 1 > matrix->cols_count) {
        return -1;
    }
    *val = matrix->elements[row * matrix->cols_count + col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return -1;
    }
    if (row + 1 > matrix->rows_count || col + 1 > matrix->cols_count) {
        return -1;
    }
    matrix->elements[row * matrix->cols_count + col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }
    Matrix* mul_scalar_matrix = create_matrix(matrix->rows_count, matrix->cols_count);
    if (mul_scalar_matrix == NULL) {
        return NULL;
    }
    double buffer;
    for (size_t i = 0; i < matrix->rows_count; ++i) {
        for (size_t j = 0; j < matrix->cols_count; ++j) {
            if (get_elem(matrix, i, j, &buffer)) {
                free_matrix(mul_scalar_matrix);
                return NULL;
            }
            if (set_elem(mul_scalar_matrix, i , j, buffer * val)) {
                free_matrix(mul_scalar_matrix);
                return NULL;
            }
        }
    }
    return mul_scalar_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    Matrix* transp_matrix = create_matrix(matrix->cols_count, matrix->rows_count);
    if (transp_matrix == NULL) {
        return NULL;
    }
    double buffer;
    for (size_t i = 0; i < matrix->rows_count; ++i) {
        for (size_t j = 0; j < matrix->cols_count; ++j) {
            if (get_elem(matrix, i, j, &buffer)) {
                free_matrix(transp_matrix);
                return NULL;
            }
            if (set_elem(transp_matrix, j, i, buffer)) {
                free_matrix(transp_matrix);
                return NULL;
            }
        }
    }
    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    if (l->rows_count != r->rows_count || l->cols_count != r->cols_count) {
        return NULL;
    }
    Matrix* sum_matrix = create_matrix(l->rows_count, l->cols_count);
    if (sum_matrix == NULL) {
        return NULL;
    }
    double buffer_l, buffer_r;
    for (size_t i = 0; i < sum_matrix->rows_count; ++i) {
        for (size_t j = 0; j < sum_matrix->cols_count; ++j) {
            if (get_elem(l, i, j, &buffer_l) || get_elem(r, i, j, &buffer_r)) {
                free_matrix(sum_matrix);
                return NULL;
            }
            if (set_elem(sum_matrix, i , j, buffer_l + buffer_r)) {
                free_matrix(sum_matrix);
                return NULL;
            }
        }
    }
    return sum_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    if (l->rows_count != r->rows_count || l->cols_count != r->cols_count) {
        return NULL;
    }
    Matrix* sub_matrix = create_matrix(l->rows_count, l->cols_count);
    if (sub_matrix == NULL) {
        return NULL;
    }
    double buffer_l, buffer_r;
    for (size_t i = 0; i < sub_matrix->rows_count; ++i) {
        for (size_t j = 0; j < sub_matrix->cols_count; ++j) {
            if (get_elem(l, i, j, &buffer_l) || get_elem(r, i, j, &buffer_r)) {
                free_matrix(sub_matrix);
                return NULL;
            }
            if (set_elem(sub_matrix, i , j, buffer_l + buffer_r)) {
                free_matrix(sub_matrix);
                return NULL;
            }
        }
    }
    return sub_matrix;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    if (l->cols_count != r->rows_count) {
        return NULL;
    }
    Matrix* mul_matrix = create_matrix(l->rows_count, r->cols_count);
    if (mul_matrix == NULL) {
        return NULL;
    }
    double summ = 0;
    double buffer_l, buffer_r;
    for (size_t j = 0; j < r->cols_count; ++j) {
        for (size_t i = 0; i < l->rows_count; ++i) {
            for (size_t k = 0; k < l->cols_count; ++k) {
                if (get_elem(l, i, k, &buffer_l) || get_elem(r, k, j, &buffer_r)) {
                    free_matrix(mul_matrix);
                    return NULL;
                }
                summ += buffer_l * buffer_r;
            }
            if (set_elem(mul_matrix, i, j, summ)) {
                free_matrix(mul_matrix);
                    return NULL;
            }
            summ = 0;
        }
    }
    return mul_matrix;
}
