#pragma once

#include "filter.hpp"

class MatrixFilter : public Filter {
    Matrix<double> matrix_;

public:
    explicit MatrixFilter(const Matrix<double>& matrix);

    ~MatrixFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
