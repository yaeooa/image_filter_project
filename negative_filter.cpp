#include "negative_filter.hpp"

Picture NegativeFilter::operator()(const Picture& pic) const {
    Picture res = pic;
    for (size_t i = 0; i < res.Height(); ++i) {
        for (size_t j = 0; j < res.Width(); ++j) {
            res[{i, j}] = {1 - pic[{i, j}].red, 1 - pic[{i, j}].green, 1 - pic[{i, j}].blue};
        }
    }
    return res;
}
