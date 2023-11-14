#pragma once

#include "filter.hpp"

class GrayscaleFilter : public Filter {
    double red_coef_;
    double green_coef_;
    double blue_coef_;

public:
    GrayscaleFilter();

    ~GrayscaleFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
