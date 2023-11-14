#pragma once

#include "filter.hpp"

class PixellateFilter : public Filter {
    size_t height_, width_;

public:
    PixellateFilter(size_t height, size_t width);

    ~PixellateFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
