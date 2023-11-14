#include "constants.hpp"
#include "grayscale_filter.hpp"

Picture GrayscaleFilter::operator()(const Picture& pic) const {
    Picture res = pic;
    for (size_t i = 0; i < res.Height(); ++i) {
        for (size_t j = 0; j < res.Width(); ++j) {
            res[{i, j}] =
                    Pixel(pic[{i, j}].red * red_coef_ + pic[{i, j}].green * green_coef_ +
                          pic[{i, j}].blue * blue_coef_);
        }
    }
    return res;
}

GrayscaleFilter::GrayscaleFilter() {
    red_coef_ = GRAYSCALE_RED_COEF;
    green_coef_ = GRAYSCALE_GREEN_COEF;
    blue_coef_ = GRAYSCALE_BLUE_COEF;
}
