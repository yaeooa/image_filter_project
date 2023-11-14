#include "crop_filter.hpp"

Picture CropFilter::operator()(const Picture& pic) const {
    Picture res = pic;
    res.Resize(height_, width_);
    return res;
}

CropFilter::CropFilter(size_t height, size_t width) : height_(height), width_(width) {
}
