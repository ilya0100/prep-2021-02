#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols) {
        rowsCount = rows;
        colsCount = cols;
        for (size_t i = 0; i < rowsCount * colsCount; i++) {
            elements.push_back(0);
        }
    }

    Matrix::Matrix(std::istream& is) {
        is >> rowsCount >> colsCount;
        if (!is) {
            throw InvalidMatrixStream();
        }

        double value;
        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                is >> value;
                elements.push_back(value);
                if (!is) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return rowsCount;
    }

    size_t Matrix::getCols() const {
        return colsCount;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= rowsCount || j >= colsCount) {
            throw OutOfRange(i, j, *this);
        }
        return elements[i * colsCount + j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= rowsCount || j >= colsCount) {
            throw OutOfRange(i, j, *this);
        }
        return elements[i * colsCount + j];
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (rowsCount != rhs.rowsCount || colsCount != rhs.colsCount) {
            return false;
        }

        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                if (abs(elements[i * colsCount + j] - rhs(i, j)) > std::numeric_limits<double>::epsilon()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        if (rowsCount != rhs.rowsCount || colsCount != rhs.colsCount) {
            return true;
        }

        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                if (abs(elements[i * colsCount + j] - rhs(i, j)) > std::numeric_limits<double>::epsilon()) {
                    return true;
                }
            }
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rowsCount; i++) {
            for (size_t j = 0; j < matrix.colsCount; j++) {
                os << matrix(i, j);
            }
            os << std::endl;
        }
        os << std::endl;
        return os;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (rowsCount != rhs.rowsCount || colsCount != rhs.colsCount) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < result.rowsCount; i++) {
            for (size_t j = 0; j < result.colsCount; j++) {
                result(i, j) = elements[i * colsCount + j] + rhs(i, j);
            }
        }
        return result;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (rowsCount != rhs.rowsCount || colsCount != rhs.colsCount) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < result.rowsCount; i++) {
            for (size_t j = 0; j < result.colsCount; j++) {
                result(i, j) = elements[i * colsCount + j] - rhs(i, j);
            }
        }
        return result;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (colsCount != rhs.rowsCount) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(rowsCount, rhs.colsCount);
        double sum = 0;

        for (size_t j = 0; j < rhs.colsCount; j++) {
            for (size_t i = 0; i < rowsCount; i++) {
                for (size_t k = 0; k < colsCount; k++) {
                    sum += elements[i * colsCount + k] * rhs(k, j);
                }
                result(i, j) = sum;
                sum = 0;
            }
        }
        return result;
    }

    Matrix Matrix::transp() const {
        Matrix result(colsCount, rowsCount);
        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                result(j, i) = elements[i * colsCount + j];
            }
        }
        return result;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                result(i, j) = elements[i * colsCount + j] * val;
            }
        }
        return result;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix result(matrix.rowsCount, matrix.colsCount);
        for (size_t i = 0; i < result.rowsCount; i++) {
            for (size_t j = 0; j < result.colsCount; j++) {
                result(i, j) = matrix(i, j) * val;
            }
        }
        return result;
    }

    double Matrix::det() const {
        double value = 0;
        return value;
    }

    Matrix Matrix::adj() const {
        if (rowsCount != colsCount) {
            // throw DimensionMismatch(, rhs);
        }
        Matrix result(rowsCount, colsCount);
        return result;
    }

    Matrix Matrix::inv() const {
        if (rowsCount != colsCount) {
            // throw DimensionMismatch(, rhs);
        }
        Matrix result(rowsCount, colsCount);
        return result;
    }
}  // namespace prep
