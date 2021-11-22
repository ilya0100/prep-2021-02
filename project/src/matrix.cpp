#include "matrix.h"
#include "exceptions.h"

#define EPS 1e-7

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
                if (std::abs((*this)(i, j) - rhs(i, j)) > EPS) {
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
                if (std::abs((*this)(i, j) - rhs(i, j)) > EPS) {
                    return true;
                }
            }
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rowsCount << " " << matrix.colsCount << std::endl;

        for (size_t i = 0; i < matrix.rowsCount; i++) {
            for (size_t j = 0; j < matrix.colsCount; j++) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix(i, j);
                if (j < matrix.colsCount - 1) {
                    os << " ";
                }
            }
            os << std::endl;
        }
        return os;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (rowsCount != rhs.rowsCount || colsCount != rhs.colsCount) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < result.rowsCount; i++) {
            for (size_t j = 0; j < result.colsCount; j++) {
                result(i, j) = (*this)(i, j) + rhs(i, j);
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
                result(i, j) = (*this)(i, j) - rhs(i, j);
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
                    sum += (*this)(i, k) * rhs(k, j);
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
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < rowsCount; i++) {
            for (size_t j = 0; j < colsCount; j++) {
                result(i, j) = (*this)(i, j) * val;
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
        if (rowsCount != colsCount) {
            throw DimensionMismatch(*this);
        }
        if (rowsCount == 1) {
            return (*this)(0, 0);
        }
        if (rowsCount == 2) {
            return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
        }
        double res = 0;
        double sign = 1;
        for (size_t j = 0; j < colsCount; j++) {
            Matrix minor = (*this).delRowAndCol(0, j);
            res += sign * (*this)(0, j) * minor.det();
            sign = - sign;
        }
        return res;
    }

    Matrix Matrix::adj() const {
        if (rowsCount != colsCount) {
            throw DimensionMismatch(*this);
        }
        Matrix result(rowsCount, colsCount);
        if (rowsCount == 1 && colsCount == 1) {
            result(0, 0) = 1;
            return result;
        }
        for (size_t i = 0; i < result.rowsCount; i++) {
            for (size_t j = 0; j < result.colsCount; j++) {
                if ((i + j) % 2 == 0) {
                    result(j, i) = delRowAndCol(i, j).det();
                } else {
                    result(j, i) = - delRowAndCol(i, j).det();
                }
            }
        }
        return result;
    }

    Matrix Matrix::inv() const {
        if (rowsCount != colsCount) {
            throw DimensionMismatch(*this);
        }
        double determinant = det();
        if (determinant == 0) {
            throw SingularMatrix();
        }
        return adj() * (1 / determinant);
    }

    Matrix Matrix::delRowAndCol(size_t row, size_t col) const {
        if (rowsCount == 1 || colsCount == 1) {
            return Matrix();
        }
        Matrix modMatrix(rowsCount - 1, colsCount - 1);
        size_t rowAdd = 0;
        for (size_t i = 0; i < modMatrix.rowsCount; i++) {
            if (i == row) {
                rowAdd = 1;
            }
            size_t colAdd = 0;
            for (size_t j = 0; j < modMatrix.colsCount; j++) {
                if (j == col) {
                    colAdd = 1;
                }
                modMatrix(i, j) = (*this)(i + rowAdd, j + colAdd);
            }
        }
        return modMatrix;
    }

}  // namespace prep
