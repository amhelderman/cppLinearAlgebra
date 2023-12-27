#pragma once

#include <cstdlib>
#include <cstring>
#include <cassert>

template <typename T, int rows, int cols>
class Matrix {
public:
    Matrix();
    Matrix(T data[rows][cols]);
    Matrix(const Matrix<T, rows, cols>& other);
    Matrix<T, rows, cols>& operator=(const Matrix<T, rows, cols>& other);
    ~Matrix();

    constexpr int getRows() const;
    constexpr int getCols() const;
    T get(int row, int col) const;
    void set(int row, int col, T value);

    static Matrix<T, rows, cols> identity();
    static Matrix<T, rows, cols> zero();
    static Matrix<T, rows, cols> random(T min, T max);

    Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& other) const;
    Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& other) const;

        
    // Declaration and definition for the specialized operator*
    // could replace matrix number datatype with decltype(std::declval<T>() * std::declval<U>())
    template <typename U, int otherRows, int otherCols>
    auto operator*(const Matrix<U, otherRows, otherCols>& other) const
        -> Matrix<decltype(std::declval<T>() * std::declval<U>()), rows, otherCols>
    {
        static_assert(cols == otherRows, "Matrix multiplication requires the number of columns in the first matrix to equal the number of rows in the second matrix");
        
        Matrix<decltype(std::declval<T>() * std::declval<U>()), rows, otherCols> result;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < otherCols; j++) {
                result.set(i,j,0);
                for (int k = 0; k < cols; k++) {
                    // result.data[i][j] += data[i][k] * other.get(k, j);
                    // Must use get and set.
                    result.set(i,j, result.get(i,j) + (this->get(i,k) * other.get(k,j)));

                }
            }
        }

        return result;
    }

    Matrix<T, rows, cols> operator*(T scalar) const;
    Matrix<T, rows, cols> operator/(T scalar) const;
    Matrix<T, rows, cols>& operator+=(const Matrix<T, rows, cols>& other);
    Matrix<T, rows, cols>& operator-=(const Matrix<T, rows, cols>& other);
    Matrix<T, rows, cols>& operator*=(const Matrix<T, rows, cols>& other);
    Matrix<T, rows, cols>& operator*=(T scalar);
    Matrix<T, rows, cols>& operator/=(T scalar);
    Matrix<T, rows, cols> operator-() const;
    bool operator==(const Matrix<T, rows, cols>& other) const;
    bool operator!=(const Matrix<T, rows, cols>& other) const;

    Matrix<T, cols, rows> transpose() const;
    Matrix<T, rows, cols> hadamard(const Matrix<T, rows, cols>& other) const;

    Matrix<T, rows, cols> apply(T (*function)(T)) const;
    Matrix<T, rows, cols> apply(T (*function)(T, int, int)) const;
    Matrix<T, rows, cols> apply(T (*function)(T, int, int, const Matrix<T, rows, cols>&)) const;
    Matrix<T, rows, cols> apply(T (*function)(T, int, int, const Matrix<T, rows, cols>&, const Matrix<T, rows, cols>&)) const;

private:
    T data[rows][cols];
};

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::Matrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0;
        }
    }
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::Matrix(T data[rows][cols]) {
    memcpy(this->data, data, sizeof(T) * rows * cols);
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::Matrix(const Matrix<T, rows, cols>& other) {
    memcpy(this->data, other.data, sizeof(T) * rows * cols);
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator=(const Matrix<T, rows, cols>& other) {
    if (this != &other) {
        memcpy(this->data, other.data, sizeof(T) * rows * cols);
    }
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::~Matrix() {
    // Destructor is empty because there are no dynamic allocations
}

template <typename T, int rows, int cols>
constexpr int Matrix<T, rows, cols>::getRows() const {
    return rows;
}

template <typename T, int rows, int cols>
constexpr int Matrix<T, rows, cols>::getCols() const {
    return cols;
}

template <typename T, int rows, int cols>
T Matrix<T, rows, cols>::get(int row, int col) const {
    return data[row][col];
}

template <typename T, int rows, int cols>
void Matrix<T, rows, cols>::set(int row, int col, T value) {
    data[row][col] = value;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::identity() {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows && i < cols; i++) {
        result.data[i][i] = 1;
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::zero() {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = 0;
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::random(T min, T max) {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = static_cast<T>(rand()) / (RAND_MAX + 1) * (max - min) + min;
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator+(const Matrix<T, rows, cols>& other) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-(const Matrix<T, rows, cols>& other) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}


template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator*(T scalar) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator/(T scalar) const {
    assert(scalar != 0); // Check for division by zero
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] / scalar;
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator+=(const Matrix<T, rows, cols>& other) {
    *this = *this + other;
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator-=(const Matrix<T, rows, cols>& other) {
    *this = *this - other;
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(const Matrix<T, rows, cols>& other) {
    *this = *this * other;
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(T scalar) {
    *this = *this * scalar;
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator/=(T scalar) {
    assert(scalar != 0); // Check for division by zero
    *this = *this / scalar;
    return *this;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-() const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = -data[i][j];
        }
    }
    return result;
}

template <typename T, int rows, int cols>
bool Matrix<T, rows, cols>::operator==(const Matrix<T, rows, cols>& other) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T, int rows, int cols>
bool Matrix<T, rows, cols>::operator!=(const Matrix<T, rows, cols>& other) const {
    return !(*this == other);
}

template <typename T, int rows, int cols>
Matrix<T, cols, rows> Matrix<T, rows, cols>::transpose() const {
    Matrix<T, cols, rows> result;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            result.set(i, j, data[j][i]);
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::hadamard(const Matrix<T, rows, cols>& other) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::apply(T (*function)(T)) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = function(data[i][j]);
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::apply(T (*function)(T, int, int)) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = function(data[i][j], i, j);
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::apply(T (*function)(T, int, int, const Matrix<T, rows, cols>&)) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = function(data[i][j], i, j, *this);
        }
    }
    return result;
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::apply(T (*function)(T, int, int, const Matrix<T, rows, cols>&, const Matrix<T, rows, cols>&)) const {
    Matrix<T, rows, cols> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = function(data[i][j], i, j, *this, *this);
        }
    }
    return result;
}
