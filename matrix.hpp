#pragma once

#include "pixel.hpp"
#include <vector>
#include <iostream>
#include <exception>
#include <iomanip>

template<class T>
class Matrix {
    size_t rows_{}, cols_{};
    std::vector<T> matrix_;

public:
    Matrix() = default;

    Matrix(size_t rows, size_t cols);

    Matrix(const Matrix<T>& other);

    Matrix(Matrix<T>&& other) noexcept = default;

    Matrix& operator=(const Matrix<T>& other);

    T& operator[](std::pair<size_t, size_t> index);

    T operator[](std::pair<size_t, size_t> index) const;

    [[nodiscard]] size_t Rows() const;

    [[nodiscard]] size_t Cols() const;

    auto Begin();

    auto End();

    T Sum() const;
};

template<class T>
T Matrix<T>::Sum() const {
    T res{0};
    for (size_t i = 0; i < Rows(); ++i) {
        for (size_t j = 0; j < Cols(); ++j) {
            res += (*this)[{i, j}];
        }
    }
    return res;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_.resize(other.matrix_.size());
    for (size_t i = 0; i < matrix_.size(); ++i) {
        matrix_[i] = other.matrix_[i];
    }
    return *this;
}

template<class T>
T Matrix<T>::operator[](std::pair<size_t, size_t> index) const {
    if (index.first >= Rows() || index.second >= Cols()) {
        return matrix_[0];
    }
    return matrix_[index.first * Cols() + index.second];
}

template<class T>
auto Matrix<T>::End() {
    return matrix_.end();
}

template<class T>
auto Matrix<T>::Begin() {
    return matrix_.begin();
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows_(other.rows_), cols_(other.cols_) {
    matrix_.resize(rows_ * cols_);
    for (size_t i = 0; i < other.matrix_.size(); ++i) {
        matrix_[i] = other.matrix_[i];
    }
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    matrix_ = std::vector<T>(rows * cols);
}

template<class T>
T& Matrix<T>::operator[](std::pair<size_t, size_t> index) {
    if (index.first >= Rows() || index.second >= Cols()) {
        return matrix_[0];
    }
    return matrix_[index.first * Cols() + index.second];
}

template<class T>
size_t Matrix<T>::Rows() const {
    return rows_;
}

template<class T>
size_t Matrix<T>::Cols() const {
    return cols_;
}
