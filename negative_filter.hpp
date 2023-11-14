#pragma once

#include "filter.hpp"

class NegativeFilter : public Filter {
public:
    NegativeFilter() = default;

    ~NegativeFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
