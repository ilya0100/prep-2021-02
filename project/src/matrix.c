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
    if (rows < 1 || cols < 1) {
        perror("error");
        free(new_matrix);
        return NULL;
    }
    new_matrix->elements = malloc(sizeof(double) * rows * cols);
    if (new_matrix->elements == NULL) {
        perror("error");
        free(new_matrix);
        return NULL;
    }
    return new_matrix;
}

void free_matrix(Matrix* matrix) {
    if (matrix->elements != NULL) {
        free(matrix->elements);
    }
    if (matrix != NULL) {
        free(matrix);
    }
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
            if (set_elem(mul_scalar_matrix, i, j, buffer * val)) {
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
            if (set_elem(sub_matrix, i , j, buffer_l - buffer_r)) {
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

// Extra operations
int det(const Matrix* matrix, double* val) {
    if (matrix->rows_count != matrix->cols_count) {
        return -1;
    }
    *val = determinant(matrix);
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix->rows_count != matrix->cols_count) {
        return NULL;
    }
    Matrix* adj_matrix = create_matrix(matrix->rows_count, matrix->cols_count);
    if (adj_matrix == NULL) {
        return NULL;
    }
    if (matrix->rows_count == 1) {
        *adj_matrix->elements = 1;
    } else {
        for (size_t i = 0; i < adj_matrix->rows_count; ++i) {
            for (size_t j = 0; j < adj_matrix->cols_count; ++j) {
                Matrix* minor = remove_row_and_col(matrix, i, j);
                if (minor == NULL) {
                    free_matrix(adj_matrix);
                    return NULL;
                }
                double element;
                if (det(minor, &element)) {
                    free_matrix(adj_matrix);
                    free_matrix(minor);
                    return NULL;
                }
                if ((i + j) % 2 == 0) {
                    set_elem(adj_matrix, j, i, element);
                } else {
                    set_elem(adj_matrix, j, i, -element);
                }
                free_matrix(minor);
            }
        }
    }
    return adj_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix->rows_count != matrix->cols_count) {
        return NULL;
    }
    double matrix_det;
    if (det(matrix, &matrix_det)) {
        return NULL;
    } else if (matrix_det == 0) {
        return NULL;
    }
    Matrix* adj_matrix = adj(matrix);
    if (adj_matrix == NULL) {
        return NULL;
    }
    Matrix* inv_matrix = mul_scalar(adj_matrix, 1 / matrix_det);
    free_matrix(adj_matrix);
    if (inv_matrix == NULL) {
        return NULL;
    }
    return inv_matrix;
}

// Additional operations
Matrix* remove_row_and_col(const Matrix* matrix, size_t row, size_t col) {
    Matrix* modified_matrix = create_matrix(matrix->rows_count - 1, matrix->cols_count - 1);
    if (modified_matrix == NULL) {
        return NULL;
    }
    size_t row_add = 0;
    double buffer;
    for (size_t i = 0; i < modified_matrix->rows_count; ++i) {
        if (i == row) {
            row_add = 1;
        }
        size_t col_add = 0;
        for (size_t j = 0; j < modified_matrix->cols_count; ++j) {
            if (j == col) {
                col_add = 1;
            }
            if (get_elem(matrix, i + row_add, j + col_add, &buffer)) {
                free_matrix(modified_matrix);
                return NULL;
            }
            if (set_elem(modified_matrix, i, j, buffer)) {
                free_matrix(modified_matrix);
                return NULL;
            }
        }
    }
    return modified_matrix;
}

double determinant(const Matrix* matrix) {
    if (matrix->rows_count == 1) {
        return matrix->elements[0];
    }
    if (matrix->rows_count == 2) {
        return matrix->elements[0] * matrix->elements[3] - matrix->elements[1] * matrix->elements[2];
    }
    double res = 0;
    double sign = 1;
    double buffer = 0;
    for (size_t j = 0; j < matrix->cols_count; ++j) {
        get_elem(matrix, 0, j, &buffer);
        Matrix* minor = remove_row_and_col(matrix, 0, j);
        res += sign * buffer * determinant(minor);
        sign = - sign;
        free_matrix(minor);
    }
    return res;
}
