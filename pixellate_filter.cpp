#include "pixellate_filter.hpp"
#include "crop_filter.hpp"

PixellateFilter::PixellateFilter(size_t height, size_t width) : height_(height), width_(width) {
}

Picture PixellateFilter::operator()(const Picture& pic) const {
    Picture tmp_pic = CropFilter(pic.Height() - pic.Height() % height_, pic.Width() - pic.Width() % width_)(pic);
    size_t x_delta = tmp_pic.Height() / height_;
    size_t y_delta = tmp_pic.Width() / width_;
    Picture res = CropFilter(height_, width_)(tmp_pic);
    for (size_t i = 0; i < tmp_pic.Height(); i += x_delta) {
        for (size_t j = 0; j < tmp_pic.Width(); j += y_delta) {
            Pixel tmp = {};
            for (size_t i1 = 0; i1 < x_delta; ++i1) {
                for (size_t j1 = 0; j1 < y_delta; ++j1) {
                    tmp += tmp_pic[{i + i1, j + j1}] / static_cast<double>(x_delta * y_delta);
                }
            }
            res[{i / x_delta, j / y_delta}] = tmp;
        }
    }
    return res;
}
