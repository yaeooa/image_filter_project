#pragma once

#include "matrix_filter.hpp"

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter();

    ~SharpeningFilter() override = default;

    using MatrixFilter::operator();
};
