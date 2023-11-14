#pragma once

#include "filter.hpp"

class CropFilter : public Filter {
    size_t height_, width_;

public:
    CropFilter(size_t height, size_t width);

    ~CropFilter() override = default;

    Picture operator()(const Picture& pic) const override;
};
