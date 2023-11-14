#pragma once

#include "matrix_filter.hpp"

class EdgeFilter : MatrixFilter {
    double threshold_;

public:
    explicit EdgeFilter(double threshold);

    ~EdgeFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
