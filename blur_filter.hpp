#pragma once

#include "filter.hpp"
#include "picture.hpp"

class BlurFilter : public Filter {
    double sigma_;

public:
    explicit BlurFilter(double sigma);

    ~BlurFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
